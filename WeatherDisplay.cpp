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
		{ B00000000, B00000000, B00000000, B00000000, B00000001, B00000010, B00000010, B00000100 }, //
		{ B00010000, B00001000, B00000100, B11110001, B00001111, B00000001, B00000001, B00000000 }, //
		{ B10000100, B10001000, B00010000, B11000000, B11100000, B11110110, B11110000, B11100000 }, //
//
		{ B00001000, B00001000, B00000111, B00000000, B00000000, B00000001, B00000000, B00000001 }, //
		{ B00000000, B00000000, B10101010, B01010100, B10101000, B01010000, B10000000, B00000000 }, //
		{ B01000000, B01001000, B10000100, B00000010, B00000000, B00000000, B00000000, B00000000 }, //
//
// ICON_IDX_PARTLY_SUNNY
		{ B00000000, B00000000, B00000000, B00000000, B00000001, B00000010, B00000010, B00000100 }, //
		{ B00010000, B00001000, B00000100, B11110001, B00001111, B00000001, B00000001, B00000000 }, //
		{ B10000100, B10001000, B00010000, B11000000, B11100000, B11110110, B11110000, B11100000 }, //
//
		{ B00001000, B00001000, B00000111, B00000000, B00000000, B00000000, B00000000, B00000000 }, //
		{ B00000000, B00000000, B11111111, B00000000, B00000000, B00000000, B00000000, B00000000 }, //
		{ B01000000, B01001000, B10000100, B00000010, B00000000, B00000000, B00000000, B00000000 }, //
//
// ICON_IDX_RAIN
		{ B00000000, B00000000, B00000000, B00000000, B00000001, B00000010, B00000010, B00000100 }, //
		{ B00000000, B00000000, B00000000, B11110000, B00001111, B00000000, B00000000, B00000000 }, //
		{ B00000000, B00000000, B00000000, B00000000, B10000000, B01000000, B00100000, B00100000 }, //
//
		{ B00001000, B00001000, B00000111, B00000000, B00000000, B00000001, B00000000, B00000001 }, //
		{ B00000000, B00000000, B10101010, B01010100, B10101000, B01010000, B10000000, B00000000 }, //
		{ B01000000, B01000000, B10000000, B00000000, B00000000, B00000000, B00000000, B00000000 }, //
//
// ICON_IDX_THUNDERSTORM
		{ B00000000, B00000000, B00000000, B00000000, B00000001, B00000010, B00000010, B00000100 }, //
		{ B00000000, B00000000, B00000000, B11110000, B00001111, B00000000, B00000000, B00000000 }, //
		{ B00000000, B00000000, B00000000, B00000000, B10000000, B01000000, B00100000, B00100000 }, //
//
		{ B00001000, B00001000, B00000111, B00000000, B00000000, B00000000, B00000000, B00000000 }, //
		{ B00000010, B00000100, B11001001, B00010000, B00111100, B00001000, B00010000, B00100000 }, //
		{ B01000000, B01000000, B10000000, B00000000, B00000000, B00000000, B00000000, B00000000 }, //
//
// ICON_IDX_MIX_SUN_THUNDERSTORM
		{ B00000000, B00000000, B00000000, B00000000, B00000001, B00000010, B00000010, B00000100 }, //
		{ B00010000, B00001000, B00000100, B11110001, B00001111, B00000001, B00000001, B00000000 }, //
		{ B10000100, B10001000, B00010000, B11000000, B11100000, B11110110, B11110000, B11100000 }, //
//
		{ B00001000, B00001000, B00000111, B00000000, B00000000, B00000000, B00000000, B00000000 }, //
		{ B00000010, B00000100, B11001001, B00010000, B00111100, B00001000, B00010000, B00100000 }, //
		{ B01000000, B01000000, B10000000, B00000000, B00000000, B00000000, B00000000, B00000000 }, //
//
// ICON_IDX_MOON
		{ B00000000, B01000010, B00010000, B00000000, B00000100, B00100001, B00001001, B01000001 }, //
		{ B00000000, B00111100, B01111000, B11110000, B11100000, B11100000, B11110000, B11110000 }, //
		{ B00000000, B10000010, B00010000, B01000100, B00000000, B00010000, B10000010, B01000000 }, //
//
		{ B00010001, B01000001, B00010000, B00000100, B00100000, B00000010, B01000000, B00010000 }, //
		{ B11111000, B11111000, B11111100, B01111111, B00111111, B00011111, B10000111, B00000000 }, //
		{ B00000000, B00000100, B00000000, B11000001, B11000100, B10000000, B00000010, B00010000 }, //
// ICON_ERROR
		{ B01010101, B01010101, B01010101, B01010101, B01010101, B01010101, B01010101, B01010101 }, //
		{ B01010101, B01010101, B01010101, B01010101, B01010101, B01010101, B01010101, B01010101 }, //
		{ B01010101, B01010101, B01010101, B01010101, B01010101, B01010101, B01010101, B01010101 }, //
//
		{ B01010101, B01010101, B01010101, B01010101, B01010101, B01010101, B01010101, B01010101 }, //
		{ B01010101, B01010101, B01010101, B01010101, B01010101, B01010101, B01010101, B01010101 }, //
		{ B01010101, B01010101, B01010101, B01010101, B01010101, B01010101, B01010101, B01010101 }, //
//
// ICON_IDX_MIX_SUN_SNOW
		{ B00000000, B00000000, B00000000, B00000000, B00000001, B00000010, B00000010, B00000100 }, //
		{ B00010000, B00001000, B00000100, B11110001, B00001111, B00000001, B00000001, B00000000 }, //
		{ B10000100, B10001000, B00010000, B11000000, B11100000, B11110110, B11110000, B11100000 }, //
//
		{ B00001000, B00001000, B00000111, B00000000, B00000000, B00000001, B00000011, B00000001 }, //
		{ B00000000, B00100000, B01110000, B00100000, B00000100, B00001110, B10000100, B00000000 }, //
		{ B01000000, B01001000, B10000100, B00000010, B00000000, B00000000, B00000000, B00000000 }, //
//
// ICON_IDX_SNOW
		{ B00100000, B01110000, B00100000, B00000000, B00001000, B00011100, B00001000, B00000000 }, //
		{ B00000000, B00000100, B00001110, B00000100, B00000000, B00001000, B00011100, B00001000 }, //
		{ B00000000, B00010000, B00111000, B00010000, B00000000, B00000100, B00001110, B00000100 }, //
//
		{ B00000010, B00000111, B00100010, B01110000, B00100000, B00000100, B00001110, B00000100 }, //
		{ B00000000, B00000000, B00010000, B00111000, B00010000, B00000100, B00001110, B00000100 }, //
		{ B01000000, B11100000, B01000000, B00000000, B00100000, B01110000, B00100000, B00000000 }, //
//
// ICON_IDX_CLOUDY
		{ B00000000, B00000000, B00000000, B00000000, B00000001, B00000010, B00000010, B00000100 }, //
		{ B00000000, B00000011, B00001100, B11110000, B00001110, B00000001, B00000001, B00000000 }, //
		{ B00000000, B00000000, B10000000, B01000000, B01000000, B00100000, B00010000, B10001000 }, //
//
		{ B00001000, B00001000, B00000111, B00000000, B00000000, B00000000, B00000000, B00000000 }, //
		{ B00000000, B00000000, B11111111, B00000000, B00000000, B00000000, B00000000, B00000000 }, //
		{ B01001000, B01001000, B10010000, B01000000, B00000000, B00000000, B00000000, B00000000 }, //
//
// ICON_IDX_SUNNY
		{ B00000000, B00000001, B00000000, B00010000, B00000100, B00000000, B00000001, B00000001 }, //
		{ B00010000, B00010000, B10000001, B00111100, B11111111, B11111111, B11111111, B11111111 }, //
		{ B00000000, B10000000, B00000000, B00000000, B00001000, B00100000, B10000000, B10000000 }, //
//
		{ B00010101, B00000001, B00000000, B00000000, B00000100, B00010000, B00000001, B00000000 }, //
		{ B11111111, B11111111, B11111111, B11111111, B00111100, B10000001, B00010000, B00010000 }, //
		{ B10101000, B10000000, B00000000, B01000000, B00100000, B00000000, B10000000, B00000000 }, //
		};

WeatherDisplay::WeatherDisplay(Canvas *canvas, SerialAPI *serialAPI) :
		weatherTextArea(canvas, TEXT_WIDTH_PX, TEXT_ANIMATE_DELAY_MS, 1), canvas(canvas), serialAPI(serialAPI), lastWeatherRefreshMs(
				0), weatherRefreshMs(WEATHER_REFRESH_MS), iconData(alloc2DArray8(ICON_HEIGHT_PX, ICON_BYTE_WIDTH)) {
	weatherTextArea.init();

	refreshWeatherText();
	refreshIcon();
}

WeatherDisplay::~WeatherDisplay() {
	delete2DArray8(iconData);
}

void WeatherDisplay::refreshIcon() {
	uint8_t code = serialAPI->getWeather_code(1);
	uint8_t iconOffset;

	switch (code) {
	case 0:
		iconOffset = ICON_IDX_MIX_SUN_RAIN;
		break;

	case 1:
		iconOffset = ICON_IDX_PARTLY_SUNNY;
		break;

	case 2:
		iconOffset = ICON_IDX_RAIN;
		break;

	case 3:
		iconOffset = ICON_IDX_THUNDERSTORM;
		break;

	case 4:
		iconOffset = ICON_IDX_MIX_SUN_THUNDERSTORM;
		break;

	case 5:
		iconOffset = ICON_IDX_MOON;
		break;

	case 6:
		iconOffset = ICON_IDX_MIX_SUN_SNOW;
		break;

	case 7:
		iconOffset = ICON_IDX_SNOW;
		break;

	case 8:
		iconOffset = ICON_IDX_CLOUDY;
		break;

	case 9:
		iconOffset = ICON_IDX_SUNNY;
		break;

	default:
		iconOffset = ICON_ERROR;
		refreshIntervalError();
		break;
	}

	if (iconOffset == ICON_ERROR) {
		refreshIntervalError();
	} else {
		refreshIntervalOk();
	}

	copyIconData(iconOffset);
}

void inline WeatherDisplay::refreshIntervalError() {
	weatherRefreshMs = WEATHER_REFRESH_ON_ERROR_MS;
	lastWeatherRefreshMs = ms();
}

void inline WeatherDisplay::refreshIntervalOk() {
	if (weatherRefreshMs != WEATHER_REFRESH_MS) {
		weatherRefreshMs = WEATHER_REFRESH_MS;
	}
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
#if LOG_LC
			log(F("YW I: (%d,%d) = (%d,%d) = %d"), dataRow, dataCol, iconIdx, kitRow, data);
#endif
		}
		dataCol++;
		dispRowBytesIdx++;
	}

	canvas->paint(ICON_START_X_PX, ICON_START_Y_PX, ICON_WIDTH_PX, ICON_HEIGHT_PX, iconData);
}

void WeatherDisplay::refreshWeatherText() {
	cleanCharArray(buf, TEXT_BUFFER_SIZE);

	uint8_t idx = 0;

	for (uint8_t day = 1; day <= WEATHER_FORECAST_DAYS; day++) {
		if (idx >= TEXT_BUFFER_MAX_SIZE) {
			break;
		}
		// day
		idx = append(buf, idx, TEXT_BUFFER_MAX_SIZE, serialAPI->getWeather_DDD(day));
		if (day > 1) {
			buf[idx++] = '(';
			buf[idx++] = '0' + day - 1;
			buf[idx++] = ')';
		}
		buf[idx++] = 3;
		buf[idx++] = 4;
		idx = sep(idx, 1);

		// low temp
		buf[idx++] = 2;
		idx = append(buf, idx, TEXT_BUFFER_MAX_SIZE, serialAPI->getWeather_low(day));
		if (idx >= TEXT_BUFFER_MAX_SIZE) {
			break;
		}
		idx = sep(idx, 1);

		// high temp
		buf[idx++] = 1;
		idx = append(buf, idx, TEXT_BUFFER_MAX_SIZE, serialAPI->getWeather_high(day));
		idx = sep(idx, 1);

		// text
		idx = append(buf, idx, TEXT_BUFFER_MAX_SIZE, serialAPI->getWeather_text(day));
		if (idx >= TEXT_BUFFER_MAX_SIZE) {
			break;
		}
		idx = sep(idx, 5);
	}
	idx = sep(idx, 5);
	idx = append(buf, idx, TEXT_BUFFER_MAX_SIZE, serialAPI->getESPStatus());
	idx = sep(idx, 5);
	buf[idx++] = '\0';

#if LOG_LC
	log(F("YW T(%d):"), idx);
	logs(buf, TEXT_BUFFER_SIZE);
#endif

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
	if (time - lastWeatherRefreshMs < weatherRefreshMs) {
		return;
	}
	lastWeatherRefreshMs = time;
	refreshWeatherText();
	refreshIcon();
}
