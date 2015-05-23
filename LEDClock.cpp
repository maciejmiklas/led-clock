#include "LEDClock.h"
#include "SPI.h"

#define SS 10

void sendByte(const byte reg, const byte data) {
	digitalWrite(SS, LOW);
	SPI.transfer(reg);
	SPI.transfer(data);
	digitalWrite(SS, HIGH);
}

void setup() {
	pinMode(SS, OUTPUT);
	sendByte(64,64);
}

void loop() {
}
