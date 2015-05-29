#include "LEDClock.h"
#include "SPI.h"

// https://github.com/squix78/MAX7219LedMatrix

// max7219 registers
#define MAX7219_REG_NOOP         0x0
#define MAX7219_REG_DIGIT0       0x1
#define MAX7219_REG_DIGIT1       0x2
#define MAX7219_REG_DIGIT2       0x3
#define MAX7219_REG_DIGIT3       0x4
#define MAX7219_REG_DIGIT4       0x5
#define MAX7219_REG_DIGIT5       0x6
#define MAX7219_REG_DIGIT6       0x7
#define MAX7219_REG_DIGIT7       0x8
#define MAX7219_REG_DECODEMODE   0x9
#define MAX7219_REG_INTENSITY    0xA
#define MAX7219_REG_SCANLIMIT    0xB
#define MAX7219_REG_SHUTDOWN     0xC
#define MAX7219_REG_DISPLAYTEST  0xF

#define SS 22

/**
 * Transfers data to a MAX7219/MAX7221 register.
 *
 * @param address The register to load data into
 * @param value   Value to store in the register
 */
void send(uint8_t address, uint8_t value) {

	// Ensure LOAD/CS is LOW
	digitalWrite(SS, LOW);

	// Send the register address
	SPI.transfer(address);

	// Send the value
	SPI.transfer(value);

	// Tell chip to load in data
	digitalWrite(SS, HIGH);
}

void clear() {
	// clear
	send(MAX7219_REG_DIGIT0, 0);
	send(MAX7219_REG_DIGIT1, 0);
	send(MAX7219_REG_DIGIT2, 0);
	send(MAX7219_REG_DIGIT3, 0);
	send(MAX7219_REG_DIGIT4, 0);
	send(MAX7219_REG_DIGIT5, 0);
	send(MAX7219_REG_DIGIT6, 0);
	send(MAX7219_REG_DIGIT7, 0);

}
void setup() {
	delay(100);

	util_setup();
	log_setup();

	pinMode(SS, OUTPUT);

	SPI.begin();
	SPI.setDataMode(SPI_MODE3);
	SPI.setClockDivider(SPI_CLOCK_DIV128);

	// disable shutdown mode
	send(MAX7219_REG_SHUTDOWN, 1);

	// display test
	send(MAX7219_REG_DISPLAYTEST, 0);

	send(MAX7219_REG_INTENSITY, 15);  // character intensity: range: 0 to 15
	send(MAX7219_REG_SCANLIMIT, 7);   // show all 8 digits
	send(MAX7219_REG_DECODEMODE, 0);  // using an led matrix (not digits)

	clear();
}

void loop() {
	util_cycle();
	log_cycle();
	ln("start");
	for (uint8_t fontIdx = 0; fontIdx < ASCII_FONT_SIZE; fontIdx++) {
		Sprite spr = ASCII_FONT[fontIdx];
		for (uint8_t sprIdx = MAX7219_REG_DIGIT0; sprIdx <= MAX7219_REG_DIGIT7; sprIdx++) {
			send(sprIdx, spr.data[sprIdx - 1]);
		}
		ln("%02x - 0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x", fontIdx, spr.data[0], spr.data[1],
				spr.data[2], spr.data[3], spr.data[4], spr.data[5], spr.data[6], spr.data[7]);
		delay(100);
	}
	ln("end");
}

