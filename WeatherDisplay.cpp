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

WeatherDisplay::WeatherDisplay(Canvas *canvas, SerialAPI *serialAPI) :
		canvas(canvas), serialAPI(serialAPI), weatherTextArea(canvas, WEATHER_TEXT_WIDTH, WEATHER_TEXT_ANIMATE_DELAY_MS,
				1), lastWeatherRefresh(0) {
	weatherTextArea.init();

	refreshWeather();
}

WeatherDisplay::~WeatherDisplay() {
}

void WeatherDisplay::refreshWeather() {
	uint8_t idx = 0;

	for (uint8_t day = 1; day <= 3; day++) {

		// day
		idx = appendText(buf, idx, WEATHER_TEXT_BUFFER_SIZE, serialAPI->getWeather_day(day));
		buf[idx++] = 3;
		buf[idx++] = 4;
		buf[idx++] = ' ';

		// low temp
		buf[idx++] = 2;
		idx = appendText(buf, idx, WEATHER_TEXT_BUFFER_SIZE, serialAPI->getWeather_low(day));
		idx = sep(idx, 1);

		// high temp
		buf[idx++] = 1;
		idx = appendText(buf, idx, WEATHER_TEXT_BUFFER_SIZE, serialAPI->getWeather_high(day));
		idx = sep(idx, 1);

		// text
		idx = appendText(buf, idx, WEATHER_TEXT_BUFFER_SIZE, serialAPI->getWeather_text(day));
		idx = sep(idx, 5);
	}
	buf[idx++] = '\0';

#if LOG
	log(F("Weather buf: %d -> %s"), idx, buf);
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
}
