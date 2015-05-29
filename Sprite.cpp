#include <Sprite.h>

Sprite::Sprite(uint8_t width, uint8_t height, ...) {
	this->width = width;
	this->height = height;
	this->data = new uint8_t[height];

	va_list va;
	va_start(va, height);
	for (uint8_t i = 0; i < height; i++) {
		*(this->data + i) = reverse(va_arg(va, int));
	}
	va_end(va);
}

uint8_t Sprite::reverse(uint8_t in) {
	uint8_t out;
	out = 0;
	if (in & 0x01)
		out |= 0x80;
	if (in & 0x02)
		out |= 0x40;
	if (in & 0x04)
		out |= 0x20;
	if (in & 0x08)
		out |= 0x10;
	if (in & 0x10)
		out |= 0x08;
	if (in & 0x20)
		out |= 0x04;
	if (in & 0x40)
		out |= 0x02;
	if (in & 0x80)
		out |= 0x01;

	return (out);
}
