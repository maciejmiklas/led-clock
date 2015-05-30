#include "RowDisplay.h"

// max7219 registers
#define REG_NOOP         0x0
#define REG_DIGIT0       0x1
#define REG_DIGIT1       0x2
#define REG_DIGIT2       0x3
#define REG_DIGIT3       0x4
#define REG_DIGIT4       0x5
#define REG_DIGIT5       0x6
#define REG_DIGIT6       0x7
#define REG_DIGIT7       0x8
#define REG_DECODEMODE   0x9
#define REG_INTENSITY    0xA
#define REG_SCANLIMIT    0xB
#define REG_SHUTDOWN     0xC
#define REG_DISPLAYTEST  0xF

RowDisplay::RowDisplay(uint8_t ssSize, ...) {

	this->ssSize = ssSize;

	// assign varargs to #ss
	this->ss = new uint8_t[ssSize];
	va_list va;
	va_start(va, ssSize);
	for (uint8_t i = 0; i < ssSize; i++) {
		*(this->ss + i) = va_arg(va, int);
	}
	va_end(va);
}

void RowDisplay::setup() {
	SPI.begin();
	SPI.setDataMode(SPI_MODE3);
	SPI.setClockDivider(SPI_CLOCK_DIV128);

	for (uint8_t ss = 0; ss < ssSize; ss++) {
		setupMax(ss);
	}
}

void RowDisplay::setupMax(uint8_t ss) {
	pinMode(ss, OUTPUT);

	// disable shutdown mode
	send(ss, REG_SHUTDOWN, 1);

	// display test
	send(ss, REG_DISPLAYTEST, 0);

	send(ss, REG_INTENSITY, 15);  // character intensity: range: 0 to 15
	send(ss, REG_SCANLIMIT, 7);   // show all 8 digits
	send(ss, REG_DECODEMODE, 0);  // using an led matrix (not digits)
}

void RowDisplay::clear(uint8_t ss) {
	send(ss, REG_DIGIT0, 0);
	send(ss, REG_DIGIT1, 0);
	send(ss, REG_DIGIT2, 0);
	send(ss, REG_DIGIT3, 0);
	send(ss, REG_DIGIT4, 0);
	send(ss, REG_DIGIT5, 0);
	send(ss, REG_DIGIT6, 0);
	send(ss, REG_DIGIT7, 0);
}

/* Transfers data to a MAX7219. */
void RowDisplay::send(uint8_t ss, uint8_t address, uint8_t data) {

	// Ensure LOAD/CS is LOW
	digitalWrite(ss, LOW);

	// Send the register address
	SPI.transfer(address);

	// Send the value
	SPI.transfer(data);

	// Tell chip to load in data
	digitalWrite(ss, HIGH);
}
