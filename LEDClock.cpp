#include "LEDClock.h"

Display* disp;

static uint8_t** setupSS() {
	uint8_t **ss = new uint8_t*[6];
	for (int i = 0; i < 6; i++) {
		ss[i] = new uint8_t[5];
	}

	// row 0
	ss[0][0] = 22;
	ss[1][0] = 23;
	ss[2][0] = 24;
	ss[3][0] = 25;
	ss[4][0] = 26;
	ss[5][0] = 27;

	// row 1
	ss[0][1] = 28;
	ss[1][1] = 29;
	ss[2][1] = 30;
	ss[3][1] = 31;
	ss[4][1] = 32;
	ss[5][1] = 33;

	// row 2
	ss[0][2] = 34;
	ss[1][2] = 35;
	ss[2][2] = 36;
	ss[3][2] = 37;
	ss[4][2] = 38;
	ss[5][2] = 39;

	// row 3
	ss[0][3] = 40;
	ss[1][3] = 41;
	ss[2][3] = 42;
	ss[3][3] = 43;
	ss[4][3] = 44;
	ss[5][3] = 45;

	// row 4
	ss[0][4] = 46;
	ss[1][4] = 47;
	ss[2][4] = 48;
	ss[3][4] = 49;
	ss[4][4] = 50;
	ss[5][4] = 51;

	return ss;
}

void printA() {
	uint8_t **ss = setupSS();
	disp = new Display(4, 5, ss);
	disp->setup();


	uint8_t **data = new uint8_t*[4];
	for (int i = 0; i < 4; i++) {
		data[i] = new uint8_t[1];
	}

	data[0][0] = 0x92;
	data[1][0] = 0x44;
	data[2][0] = 0x2A;
	data[3][0] = 0xFF;

	disp->paint(4, 5, 8, 4, data);
}


void printB() {
	uint8_t **ss = setupSS();
	disp = new Display(6, 5, ss);
	disp->setup();


	uint8_t **data = new uint8_t*[12];
	for (int i = 0; i < 12; i++) {
		data[i] = new uint8_t[3];
	}

	// row 0
	data[0][0] = 0xBA;
	data[0][1] = 0x55;
	data[0][2] = 0x80;

	// row 1
	data[1][0] = 0x54;
	data[1][1] = 0x49;
	data[1][2] = 0x0;

	// row 2
	data[2][0] = 0xA4;
	data[2][1] = 0x48;
	data[2][2] = 0xC0;

	// row 3
	data[3][0] = 0x94;
	data[3][1] = 0x44;
	data[3][2] = 0x80;

	// row 4
	data[4][0] = 0x0;
	data[4][1] = 0x0;
	data[4][2] = 0x0;

	// row 5
	data[5][0] = 0xCA;
	data[5][1] = 0x0;
	data[5][2] = 0x80;

	// row 6
	data[6][0] = 0xA5;
	data[6][1] = 0x29;
	data[6][2] = 0x0;

	// row 7
	data[7][0] = 0xAB;
	data[7][1] = 0x2F;
	data[7][2] = 0x0;

	// row 8
	data[8][0] = 0xFF;
	data[8][1] = 0x74;
	data[8][2] = 0x80;

	// row 9
	data[9][0] = 0xA4;
	data[9][1] = 0x24;
	data[9][2] = 0x80;

	// row 10
	data[10][0] = 0x88;
	data[10][1] = 0x40;
	data[10][2] = 0x8;

	// row 11
	data[11][0] = 0x48;
	data[11][1] = 0x4C;
	data[11][2] = 0x0;

	disp->paint(18, 13, 18, 12, data);
}

void setup() {
	util_setup();
	log_setup();

	delay(10);
	printB();
}

void loop() {
	delay(1000000);
//	util_cycle();
//	log_cycle();
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

