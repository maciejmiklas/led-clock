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
#ifndef BRIGHTNESS_H_
#define BRIGHTNESS_H_

#include "ArdLog.h"
#include "DispUtil.h"
#include "Display.h"

class Brightness {
public:
	Brightness(Display* display);
	virtual ~Brightness();
	void cycle();
private:
	const static uint16_t REFRESH_MS = 100;
	const static uint8_t ANALOG_PIN = A0;
	const static uint8_t MIN_CHANGE = 100;

	const static uint8_t LEVEL_1_OUT = 5;

	const static int16_t LEVEL_2 = 800;
	const static uint8_t LEVEL_2_OUT = 10;

	const static int16_t LEVEL_3 = 700;
	const static uint8_t LEVEL_3_OUT = 15;

	uint32_t lastRefreshMs;
	int16_t lastAval;
	Display* const display;

};

#endif /* BRIGHTNESS_H_ */
