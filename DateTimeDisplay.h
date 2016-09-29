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
#ifndef DATETIMEDISPLAY_H_
#define DATETIMEDISPLAY_H_

#include "Canvas.h"
#include "StaticText8x8.h"
#include "SerialAPI.h"
#include "ArdLog.h"
#include "DipsUtil.h"

const static uint8_t TIME_SEPARATOR_FRAMES = 2;

class DateTimeDisplay {
public:
	DateTimeDisplay(Canvas *canvas, SerialAPI *serialAPI);
	virtual ~DateTimeDisplay();
	void cycle();
private:
	const static uint8_t DISPLAY_TIME_WIDTH = 40;
	const static uint8_t DISPLAY_DATE_WIDTH = 40;
	const static uint16_t DATE_SWITCH_MS = 3000;
	const static uint16_t TIME_SEPARATOR_REFRESH_MS = 1000;

	Canvas * const canvas;
	SerialAPI * const serialAPI;
	StaticText8x8 hourArea;
	StaticText8x8 dateArea;
	uint32_t lastDateSwitchMs;
	uint32_t lastTimeSeparatorRefreshMs;
	boolean showingFullDate;
	uint8_t timeSeparatorIdx;
	uint8_t ** const timeSeparatorData;

	void refreshTime();
	void refreshDate();
	void inline refreshTimeSeparaator();
	void inline copyTimeSeparatorData(uint8_t fontIdx);
};

#endif /* DATETIMEDISPLAY_H_ */
