#include "LEDClock.h"
#include "SPI.h"

// https://github.com/squix78/MAX7219LedMatrix

#define SS 22



void setup() {
	delay(100);

	util_setup();
	log_setup();


}

void loop() {
	util_cycle();
	log_cycle();
	ln("start");
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

