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

PROGMEM const uint8_t TIME_SEPARATOR_FONT[TIME_SEPARATOR_FRAMES][FONT8_HEIGHT] = { //
		{ 0x24, 0x00, 0x00, 0x24, 0x24, 0x00, 0x00, 0x24 }, // 1
				{ 0x00, 0x18, 0x18, 0x00, 0x00, 0x18, 0x18, 0x00 } // 2
		};

DateTimeDisplay::DateTimeDisplay(Canvas *canvas, SerialAPI *serialAPI) :
		canvas(canvas), serialAPI(serialAPI), hourArea(canvas, DISPLAY_TIME_WIDTH), dateArea(canvas,
				DISPLAY_DATE_WIDTH), lastDateSwitchMs(0), lastTimeSeparatorRefreshMs(0), showingFullDate(true), timeSeparatorIdx(
				0), timeSeparatorData(alloc2DArray8(FONT8_HEIGHT, 1)) {

	refreshTime();
}

DateTimeDisplay::~DateTimeDisplay() {
	delete2DArray8(timeSeparatorData);
}

void DateTimeDisplay::cycle() {
	refreshTimeSeparaator();
	refreshDate();
}

void inline DateTimeDisplay::refreshTimeSeparaator() {
	uint32_t time = ms();
	if (time - lastTimeSeparatorRefreshMs < TIME_SEPARATOR_REFRESH_MS) {
		return;
	}
	lastTimeSeparatorRefreshMs = time;
	if (timeSeparatorIdx == TIME_SEPARATOR_FRAMES) {
		timeSeparatorIdx = 0;
	}
	copyTimeSeparatorData(timeSeparatorIdx);
	canvas->paint(14, 0, FONT8_HEIGHT, FONT8_HEIGHT, timeSeparatorData);
	timeSeparatorIdx++;
}

void DateTimeDisplay::refreshDate() {
	long time = ms();
	if (time - lastDateSwitchMs < DATE_SWITCH_MS && lastDateSwitchMs != 0) {
		return;
	}
	lastDateSwitchMs = time;
	char *resp;
	if (showingFullDate) {
		resp = serialAPI->getDate_full();
	} else {
		resp = serialAPI->getDate_day();
	}
	dateArea.box(0, 8, resp);
	showingFullDate = !showingFullDate;
}

void DateTimeDisplay::refreshTime() {
	// HH
	char *resp = serialAPI->getTime_hour();
	hourArea.box(0, 0, resp);

	// mm
	resp = serialAPI->getTime_minutes();
	hourArea.box(22, 0, resp);
}

void inline DateTimeDisplay::copyTimeSeparatorData(uint8_t fontIdx) {
	for (uint8_t row = 0; row < FONT8_HEIGHT; row++) {
		timeSeparatorData[row][0] = pgm_read_byte(&TIME_SEPARATOR_FONT[fontIdx][row]);
	}
}
