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
#ifndef SERIALAPI_H_
#define SERIALAPI_H_

#include "Arduino.h"

/**
 * 4 serial hardware ports are supported: 1,2,3. If all are set to false we will use default Serial.
 */
#define API_USE_SERIAL_1 true
#define API_USE_SERIAL_2 false
#define API_USE_SERIAL_3 false

class SerialAPI {
public:
	SerialAPI();
	virtual ~SerialAPI();

	/** HH, always 2 characters. Range: 0 to 23 */
	char* getTime_hour();

	/** mm, always 2 characters. range: 1 to 60. */
	char* getTime_minutes();

	/** " Sun ", " Mon ", " Tue ", " Wed ", " Thu ", " Fri ", " Sat ", always 5 characters */
	char* getDate_day();

	/** yy-mm, always 5 characters */
	char* getDate_full();

	/** "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", always 3 characters */
	char* getWeather_day(uint8_t day);

	/** "Partly Cloudy", "Thunderstorms" or "Sunny" */
	char* getWeather_text(uint8_t day);

	/** min temp in celclus */
	char* getWeather_low(uint8_t day);

	/** max temp in celclus */
	char* getWeather_high(uint8_t day);

private:
	char sbuf[25];
	inline HardwareSerial& serial();

	/**
	 * Sends given #request into serial port and writes response into #response array. Method returns response length
	 * without terminating characters.
	 */
	uint8_t cmd(char *response, const char *request, uint8_t requestLength);
};

#endif /* SERIALAPI_H_ */
