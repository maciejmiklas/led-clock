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
#ifndef WEATHERDISPLAY_H_
#define WEATHERDISPLAY_H_

#include "Canvas.h"
#include "SerialAPI.h"
#include "DispUtil.h"
#include "ScrollingText8x8.h"

const static uint8_t WEATHER_ICON_DISPLAYS = 6;
const static uint8_t WEATHER_ICONS = 11;
const static uint8_t WEATHER_ICON_SIZE = WEATHER_ICON_DISPLAYS * WEATHER_ICONS;

class WeatherDisplay {
public:
	WeatherDisplay(Canvas *canvas, SerialAPI *serialAPI);
	virtual ~WeatherDisplay();
	void cycle();
	void init();
	ScrollingText8x8 weatherTextArea;
private:
	const static uint8_t ICON_IDX_MIX_SUN_RAIN = 0;
	const static uint8_t ICON_IDX_PARTLY_SUNNY = 6;
	const static uint8_t ICON_IDX_RAIN = 12;
	const static uint8_t ICON_IDX_THUNDERSTORM = 18;
	const static uint8_t ICON_IDX_MIX_SUN_THUNDERSTORM = 24;
	const static uint8_t ICON_IDX_MOON = 30;
	const static uint8_t ICON_EMPTY = 36;
	const static uint8_t ICON_IDX_MIX_SUN_SNOW = 42;
	const static uint8_t ICON_IDX_SNOW = 48;
	const static uint8_t ICON_IDX_CLOUDY = 54;
	const static uint8_t ICON_IDX_SUNNY = 60;

	const static uint32_t WEATHER_REFRESH_MS = 60000; // 60000 every minute
	const static uint32_t WEATHER_REFRESH_ON_ERROR_MS = 10000; // 10000 every 10 seconds
	const static uint8_t TEXT_WIDTH_PX = 64;
	const static uint8_t TEXT_ANIMATE_DELAY_MS = 20;
	const static uint8_t TEXT_BUFFER_SIZE = 255;
	const static uint8_t TEXT_BUFFER_MAX_SIZE = TEXT_BUFFER_SIZE - 10;
	const static uint8_t ICON_BYTE_WIDTH = 3;
	const static uint8_t ICON_ROWS = 2;
	const static uint8_t ICON_ROW_BYTES = 3;
	const static uint8_t ICON_BYTES = ICON_ROWS * ICON_ROW_BYTES;
	const static uint8_t ICON_HEIGHT_PX = 16;
	const static uint8_t ICON_WIDTH_PX = 24;
	const static uint8_t ICON_START_X_PX = 40;
	const static uint8_t ICON_START_Y_PX = 0;
	const static uint8_t CODES_SIZE = 5;
	const static uint16_t CODES_REFRESH_MS = 1000;
	const static uint8_t CODES_PAUSE_CYCLES = 2;

	Canvas* const canvas;
	SerialAPI* const serialAPI;
	uint32_t lastWeatherRefreshMs;
	uint16_t weatherRefreshMs;
	char buf[TEXT_BUFFER_SIZE];
	uint8_t** const iconData;
	uint8_t lastIcon;

	uint8_t codes[CODES_SIZE];
	uint8_t codesReadSize;
	uint8_t codesIxd;
	uint32_t codesLastRefreshMs;

	void refreshWeatherText(boolean force);
	void refreshIcon();
	void refreshCodes();
	uint8_t inline sep(uint8_t idx, uint8_t chars);
	void inline copyIconData(uint8_t iconIdx);
	void inline refreshWeather();

};

#endif /* WEATHERDISPLAY_H_ */
