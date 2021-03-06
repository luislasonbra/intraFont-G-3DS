/*
 * sinus.c
 * This file is used to display the PSP's internal font (pgf and bwfon firmware files)
 * intraFont Version 0.31 by BenHur - http://www.psp-programming.com/benhur
 *
 * Rotation support by Geecko
 * Uses parts of pgeFont by InsertWittyName - http://insomniac.0x89.org
 *
 * This work is licensed under the Creative Commons Attribution-Share Alike 3.0 License.
 * See LICENSE for more details.
 *
 */

#include <3ds.h>
#include <sf2d.h>
#include <intraFont.h>
#include <stdio.h>
#include <math.h>


#define WHITE RGBA8(255, 255, 255, 255)
#define BLACK RGBA8(0, 0, 0, 255)


int main()
{
	sf2d_init();
	sf2d_set_clear_color(RGBA8(0x40, 0x40, 0x40, 0xFF));

	consoleInit(GFX_BOTTOM, NULL);
	printf("intraFont test sinusoid\n");

	intraFontInit();
	intraFont *font = intraFontLoad("/ltn8.pgf", INTRAFONT_CACHE_ASCII);
	intraFontSetStyle(font, 1.0f, 0, 0, 0.0f, INTRAFONT_ALIGN_CENTER);

	struct Sinusoid {
		float angle; // In degrees
		float amplitude;
		float step;
		float speed;
		float speed_inc;
		char str[64];
	} sinus = {0.f,35.f,10.f,0.f,0.007f,"intraFont 0.31 - 2009 by BenHur"};

	float x = 0.0f;
	float y = 0.0f;
	float size = 0.65f;
	float tmp_angle;
	int i;
	u32 held;

	while (aptMainLoop()) {

		hidScanInput();
		held = hidKeysHeld();
		if (held & KEY_START) {
			break;
		} else if (held & KEY_L) {
			size += 0.1f;
		} else if (held & KEY_R) {
			size -= 0.1f;
		}
		if (held & KEY_UP) {
			y -= 3.0f;
		} else if (held & KEY_DOWN) {
			y += 3.0f;
		}
		if (held & KEY_RIGHT) {
			x += 3.0f;
		} else if (held & KEY_LEFT) {
			x -= 3.0f;
		}

		sf2d_start_frame(GFX_TOP, GFX_LEFT);

			//sf2d_draw_rectangle(50, 60, 50, 50, RGBA8(0,255,0,255));

			intraFontSetStyle(font, size, RGBA8(255,0,0,255), RGBA8(0,255,0,255), 0.0f, INTRAFONT_ALIGN_LEFT);
			intraFontPrint(font, x, y, "ola k ase");

			// * Draw the sinusoid *
			/*float draw_x = x - intraFontMeasureText(font,sinus.str)/2;
			// Get the x position of the 1st char
			// Increment the speed
			if (fabsf(sinus.speed += sinus.speed_inc) > 10.f)
				sinus.speed_inc = -sinus.speed_inc;
			// Increment the angle
			tmp_angle = (sinus.angle += sinus.speed);
			if (sinus.angle > 360.f) sinus.angle -= 360.f;

			// Draw one by one
			for (i = 0; i != strlen(sinus.str); i++, tmp_angle += sinus.step) {
				intraFontSetStyle(font, 1.0f, WHITE, BLACK, 45.f*cosf(tmp_angle*M_PI/180.f),
					INTRAFONT_ALIGN_LEFT);
				draw_x = intraFontPrintEx(font, draw_x, y + sinus.amplitude*sinf(tmp_angle*M_PI/180.f),
					sinus.str+i,1);
			}*/

		sf2d_end_frame();

		sf2d_swapbuffers();
	}

	intraFontUnload(font);
	intraFontShutdown();
	sf2d_fini();

	return 0;
}
