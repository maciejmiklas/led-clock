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
#include "SerialAPI.h"

const uint8_t CMD_SIZE = 5;
const char CMD_GET_TIME_HH[] = { 'C', 'H', 'H', '\r', '\n', '\0' };
const char CMD_GET_TIME_MM[] = { 'C', 'M', 'I', '\r', '\n', '\0' };
const char CMD_GET_DATE_DDD[] = { 'C', 'D', '3', '\r', '\n', '\0' };
const char CMD_GET_DATE_DD[] = { 'C', 'D', 'D', '\r', '\n', '\0' };
const char CMD_GET_DATE_MM[] = { 'C', 'M', 'M', '\r', '\n', '\0' };
const char CMD_GET_ESP_STATUS[] = { 'G', 'S', 'S', '\r', '\n', '\0' };

const uint8_t CMD_GET_WEATHER_DAY_IDX = 2;

const uint8_t CMD_GET_WEATHER_DAY_SIZE = 9;
char CMD_GET_WEATHER_DAY[] = { 'Y', 'F', '1', ' ', 'd', 'a', 'y', '\r', '\n', '\0' };

const uint8_t CMD_GET_WEATHER_TEXT_SIZE = 10;
char CMD_GET_WEATHER_TEXT[] = { 'Y', 'F', '1', ' ', 't', 'e', 'x', 't', '\r', '\n', '\0' };

const uint8_t CMD_GET_WEATHER_LOW_SIZE = 9;
char CMD_GET_WEATHER_LOW[] = { 'Y', 'F', '1', ' ', 'l', 'o', 'w', '\r', '\n', '\0' };

const uint8_t CMD_GET_WEATHER_HIGH_SIZE = 10;
char CMD_GET_WEATHER_HIGH[] = { 'Y', 'F', '1', ' ', 'h', 'i', 'g', 'h', '\r', '\n', '\0' };

const uint8_t CMD_GET_WEATHER_CODE_DAY_IDX = 4;
const uint8_t CMD_GET_WEATHER_CODE_SIZE = 7;
char CMD_GET_WEATHER_CODE[] = { 'Y', 'W', 'C', ' ', '1', '\r', '\n', '\0' };

SerialAPI::SerialAPI() {
	serial().begin(SERIAL_BAUD);
	cleanCharArray(sbuf, SBUF_SIZE);
	getESPStatus();
}

SerialAPI::~SerialAPI() {
}

inline void SerialAPI::readGarbage() {
	if (serial().available() <= 0) {
		return;
	}
	uint8_t idx = 0;

	while (serial().available() > 0) {
		int read = serial().read();
		if (idx < SBUF_SIZE) {
			sbuf[idx++] = read;
		}
	}
#if LOG
	if (idx > 0) {
		sbuf[idx] = '\0';
		log(F("SR G(%u):"), idx);
		logs(sbuf, SBUF_SIZE);
	}
#endif

}

void SerialAPI::cmd(const char *request) {
	cmd(request, CMD_SIZE);
}

void SerialAPI::cmd(const char *request, uint8_t cmdSize) {
	readGarbage();
	serial().write(request, cmdSize);
	serial().flush();
	uint8_t readSize = serial().readBytesUntil('\n', sbuf, SBUF_SIZE);
	sbuf[readSize] = '\0';
#if LOG
	logs(F("SR-> "), request, cmdSize);
	logs(F("SR<- "), sbuf, SBUF_SIZE);
#endif
}

char* SerialAPI::getESPStatus() {
	cmd(CMD_GET_ESP_STATUS);
	return sbuf;
}

char* SerialAPI::getTime_HH() {
	cmd(CMD_GET_TIME_HH);
	return sbuf;
}

char* SerialAPI::getTime_MM() {
	cmd(CMD_GET_TIME_MM);
	return sbuf;
}

char* SerialAPI::getDate_DDD() {
	cmd(CMD_GET_DATE_DDD);
	return sbuf;
}

char* SerialAPI::getDate_DD() {
	cmd(CMD_GET_DATE_DD);
	return sbuf;
}

char* SerialAPI::getDate_MM() {
	cmd(CMD_GET_DATE_MM);
	return sbuf;
}

uint8_t SerialAPI::getWeather_code(uint8_t day) {
	CMD_GET_WEATHER_CODE[CMD_GET_WEATHER_CODE_DAY_IDX] = '0' + day;
	cmd(CMD_GET_WEATHER_CODE, CMD_GET_WEATHER_CODE_SIZE);
	uint8_t val = sbuf[0];

	// we expect here ACSI character where numbers start with 48.
	if (val >= 48) {
		val -= 48;
	}

#if LOG
			log(F("WCD %d = %d -> %d"), day, sbuf[0], val);
#endif
	return val;
}

char* SerialAPI::getWeather_DDD(uint8_t day) {
	CMD_GET_WEATHER_DAY[CMD_GET_WEATHER_DAY_IDX] = '0' + day;
	cmd(CMD_GET_WEATHER_DAY, CMD_GET_WEATHER_DAY_SIZE);
	return sbuf;
}

char* SerialAPI::getWeather_text(uint8_t day) {
	CMD_GET_WEATHER_TEXT[CMD_GET_WEATHER_DAY_IDX] = '0' + day;
	cmd(CMD_GET_WEATHER_TEXT, CMD_GET_WEATHER_TEXT_SIZE);
	return sbuf;
}

char* SerialAPI::getWeather_low(uint8_t day) {
	CMD_GET_WEATHER_LOW[CMD_GET_WEATHER_DAY_IDX] = '0' + day;
	cmd(CMD_GET_WEATHER_LOW, CMD_GET_WEATHER_LOW_SIZE);
	return sbuf;
}

char* SerialAPI::getWeather_high(uint8_t day) {
	CMD_GET_WEATHER_HIGH[CMD_GET_WEATHER_DAY_IDX] = '0' + day;
	cmd(CMD_GET_WEATHER_HIGH, CMD_GET_WEATHER_HIGH_SIZE);
	return sbuf;
}

inline HardwareSerial& SerialAPI::serial() {
#if API_USE_SERIAL_1
	return Serial1;
#endif

#if API_USE_SERIAL_2
	return Serial2;
#endif

#if API_USE_SERIAL_3
	return Serial3;
#endif
	return Serial;
}

