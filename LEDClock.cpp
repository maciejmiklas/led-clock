#include "LEDClock.h"

static Display* disp;
static ssLine **ss;

static ssLine** setupSS() {
	ssLine **ss = new ssLine*[6];
	for (int i = 0; i < 6; i++) {
		ss[i] = new ssLine[5];
	}

	// kit-row 0
	ss[0][0] = 22;
	ss[1][0] = 23;
	ss[2][0] = 24;
	ss[3][0] = 25;
	ss[4][0] = 26;
	ss[5][0] = 27;

	// kit-row 1
	ss[0][1] = 28;
	ss[1][1] = 29;
	ss[2][1] = 30;
	ss[3][1] = 31;
	ss[4][1] = 32;
	ss[5][1] = 33;

	// kit-row 2
	ss[0][2] = 34;
	ss[1][2] = 35;
	ss[2][2] = 36;
	ss[3][2] = 37;
	ss[4][2] = 38;
	ss[5][2] = 39;

	// kit-row 3
	ss[0][3] = 40;
	ss[1][3] = 41;
	ss[2][3] = 42;
	ss[3][3] = 43;
	ss[4][3] = 44;
	ss[5][3] = 45;

	// kit-row 4
	ss[0][4] = 46;
	ss[1][4] = 47;
	ss[2][4] = 48;
	ss[3][4] = 49;
	ss[4][4] = 50;
	ss[5][4] = 51;

	return ss;
}

void setup() {
	util_setup();
	log_setup();

	ss = setupSS();
	disp = new Display(6, 5, ss);
	disp->setup();

	log_freeRAM("after setup");
}

void loop() {
	util_cycle();
	log_cycle();

	TextArea8x8 area = TextArea8x8(disp, 16);
	log_freeRAM("A");

	area.box(5, 5, 2, 58, 61);
	log_freeRAM("B");

	while (true) {
		log_freeRAM("loop");
		delay(1000000);
	}
}

