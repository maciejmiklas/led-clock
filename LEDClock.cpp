#include "LEDClock.h"

Display *disp;
DateTimeDisplay *dateTimeDisplay;
WeatherDisplay *weatherDisplay;
SerialAPI *serialAPI;
Brightness *brightness;
TempSensor *tempSensor;
TempSensorDriver * tempSensorDriver;

static ss_t **ss;

/**
 * SS:
 * 48, 46, 49, 47, 45, 43, 41, 39
 * 36, 34, 32, 30, 28, 26, 24, 22
 * 37, 35, 33, 31, 29, 27, 25, 23
 */
static ss_t** setupSelectSlaveLines() {
	uint8_t rows = 3;
	ss_t **ss = new ss_t*[rows];
	for (int i = 0; i < rows; i++) {
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

ScrollingText8x8 *sca2;
char *text2;

void setup() {
	delay(3000);
	dutil_setup();

#if ENABLE_LOGGER
	log_setup();
#endif
	delay(3000);
	serialAPI = new SerialAPI();

	ss = setupSelectSlaveLines();
	disp = new Display(8, 3, ss);
	disp->setup();
	disp->clear();
	tempSensor = new TempSensor();
	dateTimeDisplay = new DateTimeDisplay(disp, serialAPI, tempSensor);
	weatherDisplay = new WeatherDisplay(disp, serialAPI);
	brightness = new Brightness(disp);
	tempSensorDriver = new TempSensorDriver(&weatherDisplay->weatherTextArea, tempSensor);
	weatherDisplay->init();
}

void loop() {
	dutil_cycle();
#if ENABLE_LOGGER
	log_cycle();
#endif
	dateTimeDisplay->cycle();
	weatherDisplay->cycle();
	brightness->cycle();
	disp->flush();
}

