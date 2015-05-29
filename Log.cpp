#include "Log.h"

static Time lt;
static uint32_t runMs;
static uint32_t lastStatusMs = 0;
static uint16_t lastRam = 0;

void log_setup() {
	Serial.begin(115200);
	runMs = util_millis();
}

static void log_status() {
	if (util_millis() - lastStatusMs < LOG_PRINT_STATUS_MS) {
		return;
	}
	lastStatusMs = util_millis();
	uint16_t free = util_freeRam();
	if (lastRam != free) {
		lastRam = free;
		ln("Status -> Free RAM: %u", free);
	}
}

void log_cycle() {
	timer_sample(&lt, runMs);
	log_status();
}

void ln(const char *fmt, ...) {
	char buf[120];

	// print time
	sprintf(buf, ">>[%03u-%02u:%02u:%02u,%03u]-> ", lt.dd, lt.hh, lt.mm, lt.ss,
			lt.ml);
	Serial.print(buf);

	// print the message
	va_list va;
	va_start(va, fmt);
	vsprintf(buf, fmt, va);
	va_end(va);
	Serial.println(buf);
}


