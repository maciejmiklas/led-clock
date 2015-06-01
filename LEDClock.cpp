#include "LEDClock.h"
#include "SPI.h"

Display* disp;

void setup() {
	delay(10);

	util_setup();
	log_setup();

	uint8_t **ss = new uint8_t*[5];
	for (int i = 0; i < 5; i++) {
		ss[i] = new uint8_t[4];
	}

	// row 0
	ss[0][0] = 22;
	ss[1][0] = 23;
	ss[2][0] = 24;
	ss[3][0] = 25;

	// row 1
	ss[0][1] = 26;
	ss[1][1] = 27;
	ss[2][1] = 28;
	ss[3][1] = 29;

	// row 2
	ss[0][2] = 30;
	ss[1][2] = 31;
	ss[2][2] = 32;
	ss[3][2] = 33;

	// row 3
	ss[0][3] = 34;
	ss[1][3] = 35;
	ss[2][3] = 36;
	ss[3][3] = 37;

	// row 4
	ss[0][4] = 38;
	ss[1][4] = 39;
	ss[2][4] = 40;
	ss[3][4] = 41;

	disp = new Display(4, 5, ss);
	disp->setup();

	for (int i = 0; i < 32; i++) {
		debug("GO %d",i);
		disp->print(i, 0, 5, 3, ss);
	}
}

void loop() {
	util_cycle();
	log_cycle();
//	log("start");
//	for (uint8_t fontIdx = 0; fontIdx < ASCII_FONT_SIZE; fontIdx++) {
//		Sprite spr = ASCII_FONT[fontIdx];
//		for (uint8_t sprIdx = MAX7219_REG_DIGIT0; sprIdx <= MAX7219_REG_DIGIT7; sprIdx++) {
//			send(sprIdx, spr.data[sprIdx - 1]);
//		}
//		ln("%02x - 0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x", fontIdx, spr.data[0], spr.data[1],
//				spr.data[2], spr.data[3], spr.data[4], spr.data[5], spr.data[6], spr.data[7]);
//		delay(100);
//	}
//	ln("end");
}

