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
const static uint8_t WEATHER_ICONS = 7;
const static uint8_t WEATHER_ICON_SIZE = WEATHER_ICON_DISPLAYS * WEATHER_ICONS;

class WeatherDisplay {
public:
	WeatherDisplay(Canvas *canvas, SerialAPI *serialAPI);
	virtual ~WeatherDisplay();
	void cycle();
private:
	const static uint8_t ICON_IDX_MIX_SUN_RAIN = 0;
	const static uint8_t ICON_IDX_PARTLY_SUNNY = 6;
	const static uint8_t ICON_IDX_RAIN = 12;
	const static uint8_t ICON_IDX_THUNDERSTORM = 18;
	const static uint8_t ICON_IDX_MIX_SUN_THUNDERSTORM = 24;
	const static uint8_t ICON_IDX_MOON = 30;
	const static uint8_t ICON_IDX_MOO1 = 36;

	const static uint32_t WEATHER_REFRESH_MS = 60000; // 3600000 every hour
	const static uint8_t TEXT_WIDTH_PX = 64;
	const static uint16_t TEXT_ANIMATE_DELAY_MS = 50;
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

	Canvas* const canvas;
	SerialAPI* const serialAPI;
	ScrollingText8x8 weatherTextArea;
	uint32_t lastWeatherRefresh;
	char buf[TEXT_BUFFER_SIZE];
	uint8_t** const iconData;

	void refreshWeather();
	void refreshIcon();
	uint8_t inline sep(uint8_t idx, uint8_t chars);
	void inline copyIconData(uint8_t iconIdx);
};

#endif /* WEATHERDISPLAY_H_ */
