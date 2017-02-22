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
#include "ArdLog.h"
#include "DispUtil.h"

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

	/** Return ESP debug info. */
	char* getESPStatus();

	// time of local time in 24h format. HH and MM have always 2 characters.
	char* getTime_HH();
	char* getTime_MM();

	/** "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT", always 3 characters */
	char* getDate_DDD();

	/** DD, always 2 characters */
	char* getDate_DD();

	/** DD, always 2 characters */
	char* getDate_MM();

	/** "Partly Cloudy", "Thunderstorms" or "Sunny" */
	char* getWeather_text(uint8_t day);

	/** min temp in celclus */
	char* getWeather_low(uint8_t day);

	/** max temp in celclus */
	char* getWeather_high(uint8_t day);

	uint8_t getWeather_code(uint8_t day);

	/** "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT", always 3 characters */
	char* getWeather_DDD(uint8_t day);

	/** read remaining data from serial to prevent errors */
	inline void readGarbage();

private:
	const static uint32_t SERIAL_BAUD = 115200;

	// keep a large buffer in order to be able to show possible errors
	const static uint8_t SBUF_SIZE = 64;
	char sbuf[SBUF_SIZE];
	inline HardwareSerial& serial();

	/**
	 * Sends given #request into serial port and writes response into #response array. Method returns response length
	 * without terminating characters.
	 */
	void cmd(const char *request);
	void cmd(const char *request, uint8_t cmdSize);
};

#endif /* SERIALAPI_H_ */
