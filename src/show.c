/*
 * STM32 PALdemo, composite video demonstration
 */

#include <stdlib.h>
#include <string.h>
#include "video.h"
#include "gdi.h"

void DelayMs(uint32_t nTime);

volatile int Paused;					// flags Alt screen active

const uint16_t	deBadBoys0[] = {
	0b0000000000000000,
	0b0000000000000000,
	0b0000011111000000,
	0b0001111111110000,
	0b0011111111111000,
	0b0011001110011000,
	0b0011111111111000,
	0b0000110001100000,
	0b0001101110110000,
	0b0011000000011000,
	0b0000000000000000,
	0b0000000000000000 };

const uint16_t	deBadBoys1[] = {
	0b0000000000000000,
	0b0000000000000000,
	0b0000011111000000,
	0b0001111111110000,
	0b0011111111111000,
	0b0011001110011000,
	0b0011111111111000,
	0b0000110001100000,
	0b0001101110110000,
	0b0001100000110000,
	0b0000000000000000,
	0b0000000000000000 };

const uint16_t	deBadBoys2[] = {
	0b0000000000000000,
	0b0000000000000000,
	0b0000011111000000,
	0b0001111111110000,
	0b0011111111111000,
	0b0011001110011000,
	0b0011111111111000,
	0b0000110001100000,
	0b0001101110110000,
	0b0000110001100000,
	0b0000000000000000,
	0b0000000000000000 };

/**
  * @brief  Handles USER button pressed
  * @retval None
  */
void USERaction(void)
{
	if (!Paused) {
		gdiDrawTextEx(120, 40, "!@#$%^&*( gy+_)({*}");
	}
	Paused = !Paused;
}

void introScreen(char *subtitle)
{
	vidClearScreen();
	gdiDrawTextEx(120, 40, KOPTEKST);
	gdiDrawTextEx(100, 50, SUBTITEL);
	DelayMs(2000); gdiDrawTextEx(110, 60, subtitle);
	DelayMs(3000);
}

void show(void)
{
	int16_t		x1, y1, x2, y2, i;

//	Demo Point
	introScreen("point demonstration");
	for (i = 0; i < 500; i++) {
		DelayMs(10);
		x1 = rand() % VID_PIXELS_X;
		y1 = rand() % VID_PIXELS_Y;
		gdiPoint(NULL,x1,y1);
	}
	DelayMs(3000);

//	Demo Line
	introScreen("line demonstration");
	for (i = 0; i < 50; i++) {
		DelayMs(150);
		x1 = rand() % VID_PIXELS_X;
		y1 = rand() % VID_PIXELS_Y;
		x2 = rand() % VID_PIXELS_X;
		y2 = rand() % VID_PIXELS_Y;
		gdiLine(NULL,x1,y1,x2,y2);
	}
	DelayMs(3000);

//	Demo Rectangle
	introScreen("rectangle demonstration");
	for (i = 0; i < 15; i++) {
		DelayMs(600);
		x1 = rand() % VID_PIXELS_X;
		y1 = rand() % VID_PIXELS_Y;
		x2 = rand() % 100;
		y2 = rand() % 100;
		gdiRectangle(x1,y1,x2,y2);
	}
	DelayMs(3000);

#if 0
	//	Demo Circle
	vidClearScreen();
	gdiRectangle(0,0,(VID_PIXELS_X - 1),VID_VSIZE - 1,0);
	gdiDrawTextEx(180, 40, KOPTEKST, GDI_ROP_COPY);
	gdiDrawTextEx(161, 55, SUBTITEL, GDI_ROP_COPY);
	gdiDrawTextEx(165, 70, "CIRCLE DEMO", GDI_ROP_COPY);
	DelayMs(3000);
	srand(sysTicks);
	for (i = 0; i < 200; i++) {
		DelayMs(20);
		x = rand();	x = x % (VID_PIXELS_X - 1);
		y = rand();	y = y % VID_VSIZE - 1;
		x1 = rand(); x1 = x1 % 80;
		gdiCircle(x,y,x1,GDI_ROP_COPY);
	}
	DelayMs(3000);
#endif
//	Demo Bitmap
	introScreen("bitmap demonstration");
	x1 = VID_PIXELS_X / 8;
	y1 = 220;
	do {
		gdiBitBlt(NULL,x1,y1,15,12,(pBMP)((x1&1)?deBadBoys1:
				((x1&3)?deBadBoys2:deBadBoys0)));
		DelayMs(100);
	} while (x1++ < (VID_PIXELS_X * 7 / 8));
	DelayMs(3000);

// Goodbye
	introScreen("font size 6x10, 42 * 24 text");

	gdiDrawTextEx(80, 90, "ARM MCU development");
	gdiDrawTextEx(95, 120, "by E.J.W. VRIEZE");
	gdiDrawTextEx(95, 130, "~~~~~ 2016 ~~~~~");
	DelayMs(9000);
}
