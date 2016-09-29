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
#include "ScrollingText8x8.h"

class WeatherDisplay {
public:
	WeatherDisplay(Canvas *canvas, SerialAPI *serialAPI);
	virtual ~WeatherDisplay();
	void cycle();
private:
	const static uint32_t WEATHER_REFRESH_MS = 3600000; // every hour
	const static uint8_t WEATHER_TEXT_WIDTH = 64;
	const static uint16_t WEATHER_TEXT_ANIMATE_DELAY_MS = 30;
	const static uint8_t WEATHER_TEXT_BUFFER_SIZE = 150;

	Canvas * const canvas;
	SerialAPI * const serialAPI;
	ScrollingText8x8 weatherTextArea;
	uint32_t lastWeatherRefresh;
	char buf[WEATHER_TEXT_BUFFER_SIZE];

	void refreshWeather();
	uint8_t inline sep(uint8_t idx, uint8_t chars);
};

#endif /* WEATHERDISPLAY_H_ */
