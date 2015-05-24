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

#define SS 10

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
	send(MAX7219_REG_DIGIT1, 0);
	send(MAX7219_REG_DIGIT2, 0);
	send(MAX7219_REG_DIGIT3, 0);
	send(MAX7219_REG_DIGIT4, 0);
	send(MAX7219_REG_DIGIT5, 0);
	send(MAX7219_REG_DIGIT6, 0);
	send(MAX7219_REG_DIGIT7, 0);

}
void setup() {
	Serial.begin(115200);

	delay(100);
	pinMode(SS, OUTPUT);

	SPI.begin();
	SPI.setDataMode(SPI_MODE3);
	SPI.setClockDivider(SPI_CLOCK_DIV128);

	// disable shutdown mode
	send(MAX7219_REG_SHUTDOWN, 1);

	// display test
	send(MAX7219_REG_DISPLAYTEST, 1);
	delay(100);
	send(MAX7219_REG_DISPLAYTEST, 0);

	send(MAX7219_REG_INTENSITY, 15);  // character intensity: range: 0 to 15
	send(MAX7219_REG_SCANLIMIT, 7);   // show all 8 digits
	send(MAX7219_REG_DECODEMODE, 0);  // using an led matrix (not digits)
	clear();
}

void loop() {
	uint8_t row = 0;
	for (int lightRow = 8; lightRow > 0; lightRow--) {
		for (uint8_t digit = MAX7219_REG_DIGIT0; digit <= MAX7219_REG_DIGIT7; digit++) {
			uint8_t rowMask = 1;
			for (uint8_t i = 0; i < lightRow; i++) {
				send(digit, row | rowMask);
				rowMask = rowMask << 1;
				delay(10);
			}
			delay(10);
		}
		row = row | 1 << (lightRow - 1);
	}
	for (int x = 0; x < 5; x++) {
		for (int i = 15; i >= 0; i--) {
			send(MAX7219_REG_INTENSITY, i);
			delay(100);
		}
		for (int i = 0; i <= 15; i++) {
			send(MAX7219_REG_INTENSITY, i);
			delay(100);
		}
	}
	clear();
}

