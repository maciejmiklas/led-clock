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
const char CMD_GET_TIME_CHM[] = { 'C', 'H', 'M', '\r', '\n', '\0' };
const char CMD_GET_DATE_DDD[] = { 'C', 'D', '3', '\r', '\n', '\0' };
const char CMD_GET_DATE_DD_MM[] = { 'C', 'D', 'M', '\r', '\n', '\0' };
const char CMD_GET_ESP_STATUS[] = { 'G', 'S', 'S', '\r', '\n', '\0' };
const char CMD_GET_WEATHER_TEXT[] = { 'G', 'T', 'X', '\r', '\n', '\0' };
const char CMD_GET_WEATHER_TEXT_CHANGE[] = { 'G', 'T', 'C', '\r', '\n', '\0' };
const char CMD_GET_WEATHER_CODES[] = { 'W', 'F', 'C', '\r', '\n', '\0' };

const char CMD_GET_CUR_TEMP[] = { 'W', 'C', 'W', ' ', 't', 'e', 'm', 'p', '\r', '\n', '\0' };
const uint8_t CMD_GET_CUR_TEMP_SIZE = 10;

const uint8_t CMD_GET_WEATHER_DAY_IDX = 2;

SerialAPI::SerialAPI() {
	serial().begin(SERIAL_BAUD);
	serial().setTimeout(SERIAL_TIMOUT_MS);
	cleanCharArray(sbuf, SBUF_SIZE);
	getESPStatus();
}

SerialAPI::~SerialAPI() {
}

inline void SerialAPI::readGarbage() {
#if LOG_LC
	uint8_t idx = 0;
	while (serial().available() > 0) {
		int read = serial().read();
		if (idx < SBUF_SIZE) {
			sbuf[idx++] = read;
		}
	}

	if (idx > 0) {
		sbuf[idx] = '\0';
		log(F("SR G(%u):"), idx);
		logs(sbuf, SBUF_SIZE);
	}
#endif

	while (serial().available() > 0) {
		serial().read();
	}
}

void SerialAPI::cmd(const char *request) {
	cmd(request, CMD_SIZE);
}

void SerialAPI::cmd(const char *request, uint8_t cmdSize) {
#if SERIAL_ENABLE
	readGarbage();
	serial().write(request, cmdSize);
	serial().flush();

	sbuf[0] = '\0';
	uint8_t readSize = serial().readBytesUntil('\n', sbuf, SBUF_SIZE);

#if LOG_LC
	logs(F("SR-> "), request, cmdSize);
	logs(F("SR<- "), sbuf, readSize);
#endif

	sbuf[readSize] = '\0';
	readGarbage();
#endif
}

char* SerialAPI::getESPStatus() {
	cmd(CMD_GET_ESP_STATUS);
	if (sbuf[0] == 'O' && sbuf[1] == 'K') {
		sbuf[0] = '\0';
	}
	return sbuf;
}

char* SerialAPI::getTime_HH_MM() {
	cmd(CMD_GET_TIME_CHM);
	return sbuf;
}

char* SerialAPI::getDate_DDD() {
	cmd(CMD_GET_DATE_DDD);
	return sbuf;
}

boolean SerialAPI::getWeather_textChange() {
	cmd(CMD_GET_WEATHER_TEXT_CHANGE);
	return sbuf[0] == '1';
}

char* SerialAPI::getDate_DD_MM() {
	cmd(CMD_GET_DATE_DD_MM);
	return sbuf;
}

char* SerialAPI::getWeather_currentTemp() {
	cmd(CMD_GET_CUR_TEMP, CMD_GET_CUR_TEMP_SIZE);
	return sbuf;
}

boolean SerialAPI::hasError() {
	return sbuf[0] == 'E';
}

uint8_t SerialAPI::getWeather_codes(uint8_t* codes) {
	cmd(CMD_GET_WEATHER_CODES);
	if (hasError()) {
		return 0;
	}

	uint8_t read = 0;
	for (uint8_t i = 0; i < 20; i++) {
		uint8_t nextChar = sbuf[i];
		if (nextChar == '\0') {
			break;
		}
		if (nextChar == ',') {
			continue;
		}
		// we expect here ACSI character where numbers start with 48.
		if (nextChar >= 48) {
			nextChar -= 48;
		}
		codes[read++] = nextChar;
	}

	return read;
}

char* SerialAPI::getWeather_text() {
	cmd(CMD_GET_WEATHER_TEXT);
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

