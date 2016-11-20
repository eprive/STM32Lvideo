/*
 * PALdemo
 */

#ifndef	__GDI_H
#define	__GDI_H
#include <stdint.h>

//	System font

#define	GDI_SYSFONT_WIDTH		6		// Width in pixels
#define	GDI_SYSFONT_HEIGHT		10		// Height in pixels
#define	GDI_SYSFONT_OFFSET		0x20

//	RASTER OPERATION
typedef enum {
	GDI_ROP_COPY		= 0,
	GDI_ROP_BONW		= 1,
	GDI_ROP_NAND		= 2,
	GDI_ROP_XOR			= 3,
	GDI_ROP_OR			= 4
} RasterOP;

#define KOPTEKST	"STM32L100RC"
#define SUBTITEL	"PAL VIDEO DEMONSTRATION"

typedef struct
{
	int16_t		x;							// X position
	int16_t		y;							// Y position
	int16_t		w;							// Width
	int16_t		h;							// Height
} GDI_RECT, *PGDI_RECT;

/* type define a pointer to a bitmap pattern which can
 * point to a 8 or 16 bitmap wide array in RAM or ROM.
 * BitBlt can handle any of these types.
 */
typedef union {
	uint16_t *halfwords;
	const uint16_t *halfwordsROM;
	uint8_t *bytesin;
	const uint8_t *bytesinROM;
} pBMP;

#define	GDI_WINCAPTION			0x0001
#define	GDI_WINBORDER			0x0002
#define	GDI_WINCLOSEICON		0x0003

//	Text align mode

#define	GDI_WINCAPTION_LEFT		0x0000
#define	GDI_WINCAPTION_CENTER	0x0010
#define	GDI_WINCAPTION_RIGHT	0x0020
#define	GDI_WINCAPTION_MASK		0x0030

typedef struct
{
	uint16_t		style;				// Mode, see GDI_WINxxx defines
	GDI_RECT		rc;					// Absolute rectangle
	uint8_t			*caption;			// Caption text

} GDI_WINDOW, *PGDI_WINDOW;

typedef struct
{
	int16_t		w;							// Width in bits
	int16_t		h;							// Height in bits
	int16_t		wb;							// width in bytes
	int16_t		wh;							// Height in bytes
	uint8_t		*bm;						// Pointer to bitmap bits

} GDI_BITMAP, PGDI_BITMAP;

//	Function definitions

void	gdiGetClientRect(PGDI_WINDOW, PGDI_RECT);
//void	gdiCopyRect(PGDI_RECT rc1, PGDI_RECT rc2);
void	gdiBitBlt(PGDI_RECT prc, int16_t x, int16_t y, int16_t w, int16_t h, pBMP bm);
void	gdiPoint(PGDI_RECT rc, uint16_t x, uint16_t y);
void	gdiLine(PGDI_RECT prc, int16_t x0, int16_t y0, int16_t x1, int16_t y1);
void	gdiRectangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
//void	gdiRectangleEx(PGDI_RECT rc);
//void	gdiCircle(uint16_t x, uint16_t y, uint16_t r, uint16_t rop);
//void	gdiDrawWindow(PGDI_WINDOW pwin);
void	gdiDrawTextEx(int16_t x, int16_t y, char *ptext);

#endif	// __GDI_H
