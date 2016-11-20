/*
 * PALdemo
 */
#include <stddef.h>
#include <string.h>
#include "video.h"
#include "gdi.h"
//#include "mth.h"

extern const uint8_t 	gdiSystemFont[][GDI_SYSFONT_HEIGHT];

/* 		rop			Raster operation. See GDI_ROP_xxx defines */
//uint16_t rop;	// raster operation, default = COPY (noninverted)
RasterOP rop = GDI_ROP_BONW;	// raster operation, default = inverted

const uint16_t masktable[16] = {
		0b1000000000000000,
		0b1100000000000000,
		0b1110000000000000,
		0b1111000000000000,
		0b1111100000000000,
		0b1111110000000000,
		0b1111111000000000,
		0b1111111100000000,
		0b1111111110000000,
		0b1111111111000000,
		0b1111111111100000,
		0b1111111111110000,
		0b1111111111111000,
		0b1111111111111100,
		0b1111111111111110,
		0b1111111111111111,
};
static union {
	uint32_t	word;
	uint16_t	halfword[2];
} pattern, bitmask;				// pattern + mask shifted into position

const uint8_t	gdiCloseBm[] = { 	0x7f, 0xC0,
									0x7f, 0xC0,
									0x7f, 0xC0,
									0x7f, 0xC0,
									0x40, 0x40,
									0x7f, 0xC0,
									0x7f, 0xC0,
									0x7f, 0xC0,
									0x7f, 0xC0 };
/*
	Function gdiCopyRect(PGDI_RECT rc1, PGDI_RECT rc2)

	Copy rectangle rc2 to rc1

	parameters:
		rc1			Destination rectangle
		rc2			Source rectangle

	return:			none

inline void gdiCopyRect(PGDI_RECT rc1, PGDI_RECT rc2) {
	memcpy(rc1, rc2, sizeof(GDI_RECT));
}
*/
/*	Function gdiBitBlt(PGDI_RECT prc, int16_t x, int16_t y, int16_t w, int16_t h, uint8_t *bm, uint16_t rop)

	Parameters:

		prc			Clipping rectangle. All X/Y coordinates are inside "prc"
					If "prc" is NULL, the coordinates will be the entire display
					area
		x			Destination X start position
		y			Destination Y start position
		w			Bitmap width, in pixels
		h			Bitmap height, in pixels
		bm			Pointer to the bitmap start position

	return			none
*/
void gdiBitBlt(PGDI_RECT prc, int16_t x, int16_t y, int16_t w, int16_t h, pBMP bm) {
/*
 * union {
	uint32_t	word;
	uint16_t	halfword[2];
} pattern, bitmask;				// pattern + mask shifted into position
 */
int16_t todo;
uint16_t alignment;

//	Calculate clipping region

	if (prc != NULL) {
		x += prc->x;
		y += prc->y;
//??		w = min(prc->w, VID_PIXELS_X-x);	// clip X
//??		h = min(prc->w, VID_PIXELS_Y-y);	// clip Y
	}
	alignment = x & 0b0000000000001111;
	for(;--h >= 0; y++) {
		for (todo = w; todo>0;) {
			if (todo >= 9) {
				bitmask.word = (todo >= 16) ?
									0xFFFF		<< (16-alignment):
						masktable[todo-1]		<< (16-alignment);
				pattern.word = *bm.halfwords++	<< (16-alignment);
				todo -= 16;
			} else {
				bitmask.word = masktable[todo-1] << (16-alignment);
				pattern.word = *bm.bytesinROM++  << (24-alignment);
				todo -= 8;
			}
			switch(rop) {
				case GDI_ROP_COPY:
					screen[y][x>>4] &= ~bitmask.halfword[1];
					screen[y][x>>4] |=  pattern.halfword[1];
					if (bitmask.halfword[0] != 0) {
						screen[y][(x>>4)+1] &= ~bitmask.halfword[0];
						screen[y][(x>>4)+1] |=  pattern.halfword[0];
					}
					break;
				case GDI_ROP_BONW:	// inverse video
					screen[y][x>>4] |=  bitmask.halfword[1];
					screen[y][x>>4] &= ~pattern.halfword[1];
					if (bitmask.halfword[0] != 0) {
						screen[y][(x>>4)+1] |=  bitmask.halfword[0];
						screen[y][(x>>4)+1] &= ~pattern.halfword[0];
					}
					break;
				case GDI_ROP_XOR:
					screen[y][x>>4] ^= pattern.halfword[1];
					if (pattern.halfword[0] != 0)
						screen[y][(x>>4)+1] ^= pattern.halfword[0];
					break;
				case GDI_ROP_OR:
					screen[y][x>>4] |= pattern.halfword[1];
					if (pattern.halfword[0] != 0)
						screen[y][(x>>4)+1] |= pattern.halfword[0];
					break;
				case GDI_ROP_NAND:
					screen[y][x>>4] &= ~pattern.halfword[1];
					if (pattern.halfword[0] != 0)
						screen[y][(x>>4)+1] &= ~pattern.halfword[0];
					break;
			}
		}
	}
}

/*
	Function gdiPoint(PGDI_RECT rc, uint16_t x, uint16_t y)

	Show a point in x/y position using the current ROP mode

	parameters:
		x			X position
		y			Y position

	return:			none
*/
void gdiPoint(PGDI_RECT rc, uint16_t x, uint16_t y) {
	/* The bit addressing of pixels is MSB first (I2S property).
	 * so invert the lower nibble, indexing 16 pixels
	 */
	uint16_t nibble = x & 0b1111;
	x = (x & ~0b1111) + 0b1111 - nibble;
	if (x < VID_PIXELS_X && y < VID_PIXELS_Y)	// Check display area bounds
	{
		switch(rop) {
			case GDI_ROP_COPY:
			case GDI_ROP_OR:	screenBB[y][x] = 1;
								break;
			case GDI_ROP_BONW:
			case GDI_ROP_NAND:	screenBB[y][x] = 0;
								break;
			case GDI_ROP_XOR:	screenBB[y][x] ^= 1;
		}
	}
}

/*
	Function gdiLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t rop)

	Draw line using Bresenham algorithm

	This function was taken from the book:
	Interactive Computer Graphics, A top-down approach with OpenGL
	written by Emeritus Edward Angel

	parameters:
		prc			Clipping rectangle
		x1			X start position
		y1			Y start position
		x2			X end position
		y2			Y end position

	return			none
*/
void gdiLine(PGDI_RECT prc, int16_t x1, int16_t y1, int16_t x2, int16_t y2) {

int16_t		dx, dy, i, e;
int16_t		incx, incy, inc1, inc2;
int16_t		x, y;

	dx = x2 - x1;
	dy = y2 - y1;

	if(dx < 0) dx = -dx;
	if(dy < 0) dy = -dy;
	incx = 1;
	if(x2 < x1) incx = -1;
	incy = 1;
	if(y2 < y1) incy = -1;
	x = x1;
	y = y1;

	if (dx > dy) {
		gdiPoint(prc, x, y);
		e = 2*dy - dx;
		inc1 = 2 * (dy - dx);
		inc2 = 2 * dy;
		for (i = 0; i < dx; i++) {
			if (e >= 0) {
				y += incy;
				e += inc1;
			}
			else {
				e += inc2;
			}
			x += incx;
			gdiPoint(prc, x, y);
		}
	} else {
		gdiPoint(prc, x, y);
		e = 2 * dx - dy;
		inc1 = 2 * (dx - dy);
		inc2 = 2 * dx;
		for(i = 0; i < dy; i++) {
			if (e >= 0) {
				x += incx;
				e += inc1;
			} else {
				e += inc2;
			}
			y += incy;
			gdiPoint(prc, x, y);
		}
	}
}

/*
	Function gdiRectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t rop)

	Draw rectangle

	parameters:
		x1			X start position
		y1			Y start position
		x2			X end position
		y2			Y end position

	return			none
*/
void	gdiRectangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1)
{
	gdiLine(NULL,x0,y0,x1,y0);
	gdiLine(NULL,x0,y1,x1,y1);
	gdiLine(NULL,x0,y0,x0,y1);
	gdiLine(NULL,x1,y0,x1,y1);
}

/*
	Function gdiRectangleEx(PGDI_RECT rc, uint16_t rop)

	Draw rectangle

	parameters:
		rc			Struct containing the rectangle parameters
		rop			Raster operation. See GDI_ROP_xxx defines

	return			none
*/
void	gdiRectangleEx(PGDI_RECT rc, uint16_t rop)
{
	gdiRectangle(rc->x, rc->y, rc->x + rc->w, rc->y + rc->h);
}
#if 0
/*
	Function gdiCircle(int16_t x, int16_t y, int16_t r, uint16_t rop)

	Draw circle. This function uses the integer-precision math

	parameters:
		x			Circle center X position
		y			Circle center Y position
		r			Radius
		rop			Raster operation. See GDI_ROP_xxx defines

	return			none
*/
void	gdiCircle(uint16_t x, uint16_t y, uint16_t r, uint16_t rop)
{
	uint32_t		x1, y1;
	uint16_t		a;

	for (a = 0; a < 360; a++) {		
		x1 = r * mthCos(a);
		y1 = r * mthSin(a);
		gdiPoint(NULL, (x1 / 10000) + x,(y1 / 10000) + y,rop);
	}
}

/*
	Function gdiDrawText(PGDI_RECT prc, char *ptext, uint16_t style, uint16_t rop)

	Draw text inside rectangle

	parameters:
		prc			Pointer to clipping rectangle
		ptext		Pointer to text
		style		Text style (see GDI_WINCAPTION_xx defines)
		rop			Raster operation. See GDI_ROP_xxx defines

	return			none
*/
void gdiDrawText(PGDI_RECT prc, char *ptext, uint16_t style, uint16_t rop) {

char		c;
uint8_t		*ptx;
uint16_t	l, i, pos, xp;

	l = strLen(ptext) * GDI_SYSFONT_WIDTH;
	switch(style) {
		case GDI_WINCAPTION_RIGHT:		if (l < prc->w) {
											prc->x += (prc->w - l);
										}
										break;
		case GDI_WINCAPTION_CENTER:		if (l < prc->w) {
											prc->x += ((prc->w - l) / 2);
										}
										break;
	}
	l = strLen(ptext);
	xp = 1; //prc->x;
	for (i = 0; i < l; i++) {
		c = *(ptext++);
		if (c >= GDI_SYSFONT_OFFSET) {
			pos = (uint16_t) (c - GDI_SYSFONT_OFFSET) * GDI_SYSFONT_BYTEWIDTH * GDI_SYSFONT_HEIGHT;
			ptx = (uint8_t *) gdiSystemFont + pos;
			gdiBitBlt(prc, xp, 0, GDI_SYSFONT_WIDTH, GDI_SYSFONT_HEIGHT, ptx, rop);
			xp += GDI_SYSFONT_WIDTH;
			if (xp >= ((prc->x + prc->w) - GDI_SYSFONT_WIDTH)) return;
		}
	}
}
#endif

/*
	Function gdiDrawTextEx(int16_t x, int16_t y, char *ptext)

	Draw text in X/Y position using system font.

	parameters:
		x			X start position
		y			Y start position
		ptext		Pointer to text

	return			none
*/
void gdiDrawTextEx(int16_t x, int16_t y, char *ptext)
{
	char		c;

	for (; (c = *ptext++) != 0; x += GDI_SYSFONT_WIDTH)
		if (c >= GDI_SYSFONT_OFFSET)
			gdiBitBlt(NULL, x, y, GDI_SYSFONT_WIDTH, GDI_SYSFONT_HEIGHT, (pBMP) gdiSystemFont[c-GDI_SYSFONT_OFFSET]);
//	clip here if		if (x >= VID_PIXELS_X - GDI_SYSFONT_WIDTH)
		// else control character handling ...
}
#if 0
/*
	Function gdiDrawWindow(PGDI_WINDOW pwin)

	Draw window

	parameters:
		pwin		Pointer to windows struct

	return			none
*/
void	gdiDrawWindow(PGDI_WINDOW pwin) {

int16_t		i;
GDI_RECT	rc, rt;

	gdiCopyRect(&rc,&pwin->rc);
	if (pwin->style & GDI_WINCAPTION) {
		gdiCopyRect(&rt,&pwin->rc);
		rt.h = rt.y + 11;
		rt.x += 2;
		rt.y += 1;
		rc.h += 10;
		for (i = 0; i < 11; i++) {
			gdiLine(NULL,rc.x, rc.y + i, rc.x + rc.w, rc.y + i);
		}
		if (pwin->style & GDI_WINCLOSEICON) {
			gdiBitBlt(&rc, rc.w - 9, 1, 10, 9, (uint8_t *) gdiCloseBm);
			rt.w -= 11;
		} else {
			rt.w -= 1;
		}
		gdiDrawText(&rt,pwin->caption,pwin->style & GDI_WINCAPTION_MASK, GDI_ROP_XOR);
	}
	gdiRectangleEx(&rc,GDI_ROP_COPY);
}
#endif
