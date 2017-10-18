/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "DateTimeDisplay.h"

char bufTime[] = { ' ', ' ', ' ', ' ', ' ', '\0' };
char bufDate[] = { ' ', ' ', ' ', ' ', ' ', '\0' };

DateTimeDisplay::DateTimeDisplay(Canvas *canvas, SerialAPI *serialAPI, TempSensor *tempSensor) :
		canvas(canvas), serialAPI(serialAPI), tempSensor(tempSensor), timeArea(canvas, DISPLAY_TIME_WIDTH), dateArea(
				canvas, DISPLAY_DATE_WIDTH), lastDateSwitchMs(0), lastTimeRefreshMs(0), switchDispPos(1), showingTimeDots(
		true) {
}

DateTimeDisplay::~DateTimeDisplay() {
}

void DateTimeDisplay::cycle() {
	refreshTime();
	refreshDate();
}

void inline DateTimeDisplay::refreshTime() {
	uint32_t time = ms();
	if (time - lastTimeRefreshMs < TIME_REFRESH_MS) {
		return;
	}

	lastTimeRefreshMs = time;

	// HH
	char* hh = serialAPI->getTime_HH();
	bufTime[0] = hh[0];
	bufTime[1] = hh[1];

	// time separator
	if (showingTimeDots) {
		bufTime[2] = ':';
	} else {
		bufTime[2] = ' ';
	}

	// MM
	char* mm = serialAPI->getTime_MM();
	bufTime[3] = mm[0];
	bufTime[4] = mm[1];

	timeArea.box(0, 0, bufTime);

	showingTimeDots = !showingTimeDots;
}

void DateTimeDisplay::refreshDate() {
	long time = ms();
	if (time - lastDateSwitchMs < DATE_SWITCH_MS && lastDateSwitchMs != 0) {
		return;
	}

	lastDateSwitchMs = time;
	switch (switchDispPos) {

	// Date: DD-MM
	case 1: {
		char* dd = serialAPI->getDate_DD();
		bufDate[0] = dd[0];
		bufDate[1] = dd[1];
		bufDate[2] = '-';
		char* mm = serialAPI->getDate_MM();
		bufDate[3] = mm[0];
		bufDate[4] = mm[1];
	}
		break;

		// Date: DDD
	case 2: {
		char* ddd = serialAPI->getDate_DDD();
		bufDate[0] = ' ';
		bufDate[1] = ddd[0];
		bufDate[2] = ddd[1];
		bufDate[3] = ddd[2];
		bufDate[4] = ' ';
	}
		break;

		// Temp outside
	case 3: {
		cleanCharArray(bufDate, DISPLAY_DATE_CHARS);
		char* temp = serialAPI->getCurrentWeather_temp();
		append(bufDate, 2, DISPLAY_DATE_CHARS, temp);
		bufDate[0] = 6;
	}
		break;

		// Temp inside
	case 4:
	default: {
		cleanCharArray(bufDate, DISPLAY_DATE_CHARS);
		float tempIn = tempSensor->getTemp();
		dtostrf(tempIn, 5, 1, bufDate);
		bufDate[0] = 5;
	}
		switchDispPos = 0;
		break;
	}
	switchDispPos++;
	bufDate[DISPLAY_DATE_CHARS] = '\0';
	dateArea.box(0, 8, bufDate);
}
