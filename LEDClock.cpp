#include "LEDClock.h"

static Display* disp;
static ssLine **ss;

static ssLine** setupSS() {
	ssLine **ss = new ssLine*[8];
	for (int i = 0; i < 8; i++) {
		ss[i] = new ssLine[3];
	}

	// first row
	ss[0][0] = 48;
	ss[1][0] = 46;
	ss[2][0] = 49;
	ss[3][0] = 47;
	ss[4][0] = 45;
	ss[5][0] = 43;
	ss[6][0] = 41;
	ss[7][0] = 39;

	// second row
	ss[0][1] = 36;
	ss[1][1] = 34;
	ss[2][1] = 32;
	ss[3][1] = 30;
	ss[4][1] = 28;
	ss[5][1] = 26;
	ss[6][1] = 24;
	ss[7][1] = 22;

	// third row
	ss[0][2] = 37;
	ss[1][2] = 35;
	ss[2][2] = 33;
	ss[3][2] = 31;
	ss[4][2] = 29;
	ss[5][2] = 27;
	ss[6][2] = 25;
	ss[7][2] = 23;

	return ss;
}

void setup() {
	util_setup();
	log_setup();

	ss = setupSS();
	disp = new Display(8, 3, ss);
	disp->setup();
}

void loop() {
	util_cycle();
	log_cycle();

	StaticTextArea sta = StaticTextArea(disp, 48);
	for (uint8_t y = 0; y < 30; y++) {
		for (uint8_t x = 0; x < 70; x++) {
			sta.box(x, y, 6, 68, 97, 110, 105, 101, 108);
			//	delay(2000);
			disp->clear();
		}
	}

}

