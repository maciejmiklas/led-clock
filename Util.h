#ifndef DOMAIN_H_
#define DOMAIN_H_

#include "Arduino.h"

void util_setup();
void util_cycle();

void util_sort_u8(uint8_t arr[], uint8_t size);
uint32_t util_millis();
uint16_t util_freeRam();

uint16_t util_abs16(int16_t val);
uint8_t util_abs8(int8_t val);

#endif /* DOMAIN_H_ */
