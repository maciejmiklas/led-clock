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
#include "Brightness.h"

Brightness::Brightness(Display * display) :
		lastRefreshMs(0), lastAval(0), display(display) {
}

Brightness::~Brightness() {
}

void Brightness::cycle() {
	uint32_t time = ms();
	if (time - lastRefreshMs < REFRESH_MS) {
		return;
	}
	lastRefreshMs = time;
	uint16_t aval = analogRead(ANALOG_PIN);

	if(abs(aval - lastAval) < MIN_CHANGE){
		return;
	}
	lastAval = aval;

	uint8_t brightness = 0;
	if (aval <= 500) {
		brightness = 15;

	} else if (aval <= 700) {
		brightness = 10;

	} else if (aval <= 800) {
		brightness = 5;
	}
	display->brightness(brightness);
}
