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
#include "WeatherDisplay.h"

PROGMEM const uint8_t WEATHER_ICON[WEATHER_ICON_SIZE][FONT8_HEIGHT] = {
// ICON_IDX_MIX_SUN_RAIN
		{ 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000001, 0b00000010, 0b00000010, 0b00000100 }, //
		{ 0b00010000, 0b00001000, 0b00000100, 0b11110001, 0b00001111, 0b00000001, 0b00000001, 0b00000000 }, //
		{ 0b10000100, 0b10001000, 0b00010000, 0b11000000, 0b11100000, 0b11110110, 0b11110000, 0b11100000 }, //
//
		{ 0b00001000, 0b00001000, 0b00000111, 0b00000000, 0b00000000, 0b00000001, 0b00000000, 0b00000001 }, //
		{ 0b00000000, 0b00000000, 0b10101010, 0b01010100, 0b10101000, 0b01010000, 0b10000000, 0b00000000 }, //
		{ 0b01000000, 0b01001000, 0b10000100, 0b00000010, 0b00000000, 0b00000000, 0b00000000, 0b00000000 }, //
//
// ICON_IDX_PARTLY_SUNNY
		{ 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000001, 0b00000010, 0b00000010, 0b00000100 }, //
		{ 0b00010000, 0b00001000, 0b00000100, 0b11110001, 0b00001111, 0b00000001, 0b00000001, 0b00000000 }, //
		{ 0b10000100, 0b10001000, 0b00010000, 0b11000000, 0b11100000, 0b11110110, 0b11110000, 0b11100000 }, //
//
		{ 0b00001000, 0b00001000, 0b00000111, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000 }, //
		{ 0b00000000, 0b00000000, 0b11111111, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000 }, //
		{ 0b01000000, 0b01001000, 0b10000100, 0b00000010, 0b00000000, 0b00000000, 0b00000000, 0b00000000 }, //
//
// ICON_IDX_RAIN
		{ 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000001, 0b00000010, 0b00000010, 0b00000100 }, //
		{ 0b00000000, 0b00000000, 0b00000000, 0b11110000, 0b00001111, 0b00000000, 0b00000000, 0b00000000 }, //
		{ 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b10000000, 0b01000000, 0b00100000, 0b00100000 }, //
//
		{ 0b00001000, 0b00001000, 0b00000111, 0b00000000, 0b00000000, 0b00000001, 0b00000000, 0b00000001 }, //
		{ 0b00000000, 0b00000000, 0b10101010, 0b01010100, 0b10101000, 0b01010000, 0b10000000, 0b00000000 }, //
		{ 0b01000000, 0b01000000, 0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000 }, //
//
// ICON_IDX_THUNDERSTORM
		{ 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000001, 0b00000010, 0b00000010, 0b00000100 }, //
		{ 0b00000000, 0b00000000, 0b00000000, 0b11110000, 0b00001111, 0b00000000, 0b00000000, 0b00000000 }, //
		{ 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b10000000, 0b01000000, 0b00100000, 0b00100000 }, //
//
		{ 0b00001000, 0b00001000, 0b00000111, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000 }, //
		{ 0b00000010, 0b00000100, 0b11001001, 0b00010000, 0b00111100, 0b00001000, 0b00010000, 0b00100000 }, //
		{ 0b01000000, 0b01000000, 0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000 }, //
//
// ICON_IDX_MIX_SUN_THUNDERSTORM
		{ 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000001, 0b00000010, 0b00000010, 0b00000100 }, //
		{ 0b00010000, 0b00001000, 0b00000100, 0b11110001, 0b00001111, 0b00000001, 0b00000001, 0b00000000 }, //
		{ 0b10000100, 0b10001000, 0b00010000, 0b11000000, 0b11100000, 0b11110110, 0b11110000, 0b11100000 }, //
//
		{ 0b00001000, 0b00001000, 0b00000111, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000 }, //
		{ 0b00000010, 0b00000100, 0b11001001, 0b00010000, 0b00111100, 0b00001000, 0b00010000, 0b00100000 }, //
		{ 0b01000000, 0b01000000, 0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000 }, //
//
// ICON_IDX_MOON
		{ 0b00000000, 0b01000010, 0b00010000, 0b00000000, 0b00000100, 0b00100001, 0b00001001, 0b01000001 }, //
		{ 0b00000000, 0b00111100, 0b01111000, 0b11110000, 0b11100000, 0b11100000, 0b11110000, 0b11110000 }, //
		{ 0b00000000, 0b10000010, 0b00010000, 0b01000100, 0b00000000, 0b00010000, 0b10000010, 0b01000000 }, //
//
		{ 0b00010001, 0b01000001, 0b00010000, 0b00000100, 0b00100000, 0b00000010, 0b01000000, 0b00010000 }, //
		{ 0b11111000, 0b11111000, 0b11111100, 0b01111111, 0b00111111, 0b00011111, 0b10000111, 0b00000000 }, //
		{ 0b00000000, 0b00000100, 0b00000000, 0b11000001, 0b11000100, 0b10000000, 0b00000010, 0b00010000 }, //
// ICON_IDX_MOON1
		{ 0b00000000, 0b01000010, 0b00010000, 0b00000000, 0b00000100, 0b00100001, 0b00001001, 0b01000001 }, //
		{ 0b00000000, 0b00111100, 0b01111000, 0b11110000, 0b11110000, 0b11110000, 0b11111000, 0b11111000 }, //
		{ 0b00000000, 0b10000010, 0b00010000, 0b01000100, 0b00000000, 0b00010000, 0b10000010, 0b01000000 }, //
//
		{ 0b00010001, 0b01000001, 0b00010000, 0b00000100, 0b00100000, 0b00000010, 0b01000000, 0b00010000 }, //
		{ 0b11111100, 0b11111110, 0b11111111, 0b01111111, 0b00111111, 0b00011111, 0b10000111, 0b00000000 }, //
		{ 0b00000000, 0b00000100, 0b11100000, 0b11000001, 0b11000100, 0b10000000, 0b00000010, 0b00010000 }, //
//
		};

WeatherDisplay::WeatherDisplay(Canvas *canvas, SerialAPI *serialAPI) :
		canvas(canvas), serialAPI(serialAPI), weatherTextArea(canvas, TEXT_WIDTH_PX, TEXT_ANIMATE_DELAY_MS, 1), lastWeatherRefresh(
				0), iconData(alloc2DArray8(ICON_HEIGHT_PX, ICON_BYTE_WIDTH)) {
	weatherTextArea.init();

	refreshWeather();
	refreshIcon();
}

WeatherDisplay::~WeatherDisplay() {
	delete2DArray8(iconData);
}

void WeatherDisplay::refreshIcon() {
	copyIconData(ICON_IDX_PARTLY_SUNNY);
}

void inline WeatherDisplay::copyIconData(uint8_t iconIdx) {
	uint8_t iconEnd = iconIdx + ICON_BYTES;
	uint8_t dataRowOffset = 0;
	uint8_t dataCol = 0;
	uint8_t dispRowBytesIdx = 0;
	for (; iconIdx < iconEnd; iconIdx++) {
		if (dispRowBytesIdx == ICON_ROW_BYTES) {
			dataRowOffset += KIT_DIM;
			dataCol = 0;
		}
		for (uint8_t kitRow = 0; kitRow < KIT_DIM; kitRow++) {
			uint8_t dataRow = kitRow + dataRowOffset;
			uint8_t data = pgm_read_byte(&WEATHER_ICON[iconIdx][kitRow]);
			iconData[dataRow][dataCol] = data;
#if LOG
			log(F("YW I: (%d,%d) = (%d,%d) = %d"), dataRow, dataCol, iconIdx, kitRow, data);
#endif
		}
		dataCol++;
		dispRowBytesIdx++;
	}

	canvas->paint(ICON_START_X_PX, ICON_START_Y_PX, ICON_WIDTH_PX, ICON_HEIGHT_PX, iconData);
}

void WeatherDisplay::refreshWeather() {
	cleanCharArray(buf, TEXT_BUFFER_SIZE);

	uint8_t idx = 0;

	for (uint8_t day = 1; day <= 3; day++) {
		if (idx >= TEXT_BUFFER_MAX_SIZE) {
			break;
		}
		// day
		idx = appendLine(buf, idx, TEXT_BUFFER_MAX_SIZE, serialAPI->getWeather_DDD(day));
		buf[idx++] = 3;
		buf[idx++] = 4;
		buf[idx++] = ' ';

		// low temp
		buf[idx++] = 2;
		idx = appendLine(buf, idx, TEXT_BUFFER_MAX_SIZE, serialAPI->getWeather_low(day));
		idx = sep(idx, 1);

		// high temp
		buf[idx++] = 1;
		idx = appendLine(buf, idx, TEXT_BUFFER_MAX_SIZE, serialAPI->getWeather_high(day));
		idx = sep(idx, 1);

		// text
		idx = appendLine(buf, idx, TEXT_BUFFER_MAX_SIZE, serialAPI->getWeather_text(day));
		idx = sep(idx, 5);
	}
	idx = sep(idx, 5);
	idx = appendLine(buf, idx, TEXT_BUFFER_MAX_SIZE, serialAPI->getESPStatus());
	idx = sep(idx, 5);
	buf[idx++] = '\0';

//#if LOG
	log(F("YW T(%d):"), idx);
	logs(buf, TEXT_BUFFER_SIZE);
//#endif

	weatherTextArea.scroll(0, 16, ScrollingText8x8::CONTINOUS_LOOP, buf);
}

uint8_t inline WeatherDisplay::sep(uint8_t idx, uint8_t chars) {
	for (uint8_t i = 0; i < chars; i++) {
		buf[idx++] = ' ';
	}
	return idx;
}

void WeatherDisplay::cycle() {
	weatherTextArea.cycle();

	uint32_t time = ms();
	if (time - lastWeatherRefresh >= WEATHER_REFRESH_MS) {
		lastWeatherRefresh = time;
		refreshWeather();
	}
}
