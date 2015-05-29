#include "Timer.h"

#define TR__MS_SEC 1000
#define TR__SEC_DD 86400
#define TR__SEC_HH 3600
#define TR__SEC_MM 60

//long milis =  126000000 + 1440000 + 17000;// 1d 11h 24m 17s
//long milis =  345600000 + 1440000 + 17000;// 4d 0h 24m 17s
//long milis =  446400000 + 1440000 + 17000;// 5d 4h 24m 17s
void timer_sample(Time *ts, uint32_t timeMilis) {
	uint32_t milis = util_millis() - timeMilis;
	uint32_t sec = milis / TR__MS_SEC;

	// days
	ts->dd = sec / TR__SEC_DD;
	uint32_t tmp = sec - ts->dd * TR__SEC_DD;

	// hours of a day
	ts->hh = tmp / TR__SEC_HH;
	tmp -= ts->hh * TR__SEC_HH;

	// minutes of an hour
	ts->mm = tmp / TR__SEC_MM;
	tmp -= ts->mm * TR__SEC_MM;

	// seconds of a minute
	ts->ss = tmp;

	// millis of a second
	ts->ml = (milis % 1000);
}


