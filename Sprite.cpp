#include <Sprite.h>

Sprite::Sprite(uint8_t width, uint8_t height, ...) {
	this->width = width;
	this->height = height;
	this->data = new uint8_t[height];

	va_list va;
	va_start(va, height);
	for (uint8_t i = 0; i < height; i++) {
		*(this->data + i) = va_arg(va, int);
	}
	va_end(va);
}

uint8_t* Sprite::getData() {
	return this->data;
}
