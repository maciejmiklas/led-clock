#include "LEDClock.h"

Display *disp;
static ss_t **ss;

/**
 * SS:
 * 48, 46, 49, 47, 45, 43, 41, 39
 * 36, 34, 32, 30, 28, 26, 24, 22
 * 37, 35, 33, 31, 29, 27, 25, 23
 */
static ss_t** setupSS() {
	ss_t **ss = new ss_t*[3];
	for (int i = 0; i < 8; i++) {
		ss[i] = new ss_t[8];
	}

	// first row
	ss[0][0] = 48;
	ss[0][1] = 46;
	ss[0][2] = 49;
	ss[0][3] = 47;
	ss[0][4] = 45;
	ss[0][5] = 43;
	ss[0][6] = 41;
	ss[0][7] = 39;

	// second row
	ss[1][0] = 36;
	ss[1][1] = 34;
	ss[1][2] = 32;
	ss[1][3] = 30;
	ss[1][4] = 28;
	ss[1][5] = 26;
	ss[1][6] = 24;
	ss[1][7] = 22;

	// third row
	ss[2][0] = 37;
	ss[2][1] = 35;
	ss[2][2] = 33;
	ss[2][3] = 31;
	ss[2][4] = 29;
	ss[2][5] = 27;
	ss[2][6] = 25;
	ss[2][7] = 23;

	return ss;
}

Scrolling8x8TextArea *sca1;
char *text1;

Scrolling8x8TextArea *sca2;
char *text2;

Scrolling8x8TextArea *sca3;
char *text3;

void setup() {
	util_setup();
	log_setup();

	ss = setupSS();
	disp = new Display(8, 3, ss);
	disp->setup();
	disp->clear();

	sca1 = new Scrolling8x8TextArea(disp, 64, 50, 1);
	sca1->init();
	text1 = "Danielowi i Arturkowi zyczymy Wesolych Swiat Bozego Narodzenia";
	sca1->scroll(0, 0, true, text1);

	sca2 = new Scrolling8x8TextArea(disp, 64, 0, 2);
	sca2->init();
	text2 = "Wlazl kotek na plotek i mruga - ladna to piosenka nie dluga ;)";
	sca2->scroll(0, 8, true, text2);
}

void loop() {
	util_cycle();
	log_cycle();
	sca1->cycle();
	sca2->cycle();

	disp->flush();
}

