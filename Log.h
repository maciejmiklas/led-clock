#ifndef Log_H_
#define Log_H_

#include "Arduino.h"
#include "stdarg.h"
#include "Timer.h"
#include "Util.h"

/* Trigger time to print system information, like free memory. */
#define LOG_PRINT_STATUS_MS 1000

void log_setup();
void log_cycle();

void ln(const char *fmt, ...);
void de(const char *fmt, ...);

#endif /* Log_H_ */
