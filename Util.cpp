#include <Util.h>

static uint32_t cycleMs;

void util_sort_u8(uint8_t arr[], uint8_t size) {
	uint8_t i, temp, j;
	for (i = 1; i < size; i++) {
		temp = arr[i];
		j = i - 1;
		while ((temp < arr[j]) && (j >= 0)) {
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = temp;
	}
}

void util_setup() {
	util_cycle();
}

void util_cycle() {
	cycleMs = millis();
}

uint32_t util_millis() {
	return cycleMs;
}

uint16_t util_freeRam() {
	extern int __heap_start, *__brkval;
	int v;
	return (uint16_t) &v
			- (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

uint16_t util_abs16(int16_t val) {
	return val > 0 ? val : val * -1;

}
uint8_t util_abs8(int8_t val) {
	return val > 0 ? val : val * -1;
}
