#ifndef SPRITE_H_
#define SPRITE_H_
#include "Arduino.h"

// Single sprite, it consists of 8x8 pixels or less.
class Sprite {

private:

	// "width <= 8"
	uint8_t width;

	// "height <= 8"
	uint8_t height;

	// represents the sprite: each byte draws single line, where data[0] is the top line
	// and data[7] is the bottom line. Array can have maximal 8 elements, but less is
	// also possible.
	uint8_t *data;

public:
	Sprite(uint8_t width, uint8_t height, ...);

	uint8_t* getData();
};

#endif /* SPRITE_H_ */
