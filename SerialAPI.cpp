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

SerialAPI::SerialAPI() {

}

SerialAPI::~SerialAPI() {
}

uint8_t SerialAPI::cmd(char *response, const char *request, uint8_t requestLength) {
	return 0;
}

char* SerialAPI::getTime_hour() {
	sbuf[0] = '1';
	sbuf[1] = '3';
	sbuf[2] = '\0';
	return sbuf;
}

char* SerialAPI::getTime_minutes() {
	sbuf[0] = '4';
	sbuf[1] = '5';
	sbuf[2] = '\0';
	return sbuf;
}

char* SerialAPI::getDate_day() {
	sbuf[0] = ' ';
	sbuf[1] = 'M';
	sbuf[2] = 'o';
	sbuf[3] = 'n';
	sbuf[4] = ' ';
	sbuf[5] = '\0';
	return sbuf;
}

char* SerialAPI::getDate_full() {
	sbuf[0] = '2';
	sbuf[1] = '3';
	sbuf[2] = '-';
	sbuf[3] = '1';
	sbuf[4] = '0';
	sbuf[5] = '\0';
	return sbuf;
}

char* SerialAPI::getWeather_day(uint8_t day) {
	if (day == 1) {
		sbuf[0] = 'M';
		sbuf[1] = 'o';
		sbuf[2] = 'n';
		sbuf[3] = '\0';
	} else if (day == 2) {
		sbuf[0] = 'T';
		sbuf[1] = 'h';
		sbuf[2] = 'u';
		sbuf[3] = '\0';
	} else if (day == 3) {
		sbuf[0] = 'W';
		sbuf[1] = 'e';
		sbuf[2] = 'd';
		sbuf[3] = '\0';
	}
	return sbuf;
}

char* SerialAPI::getWeather_text(uint8_t day) {
	sbuf[0] = 'P';
	sbuf[1] = 'a';
	sbuf[2] = 'r';
	sbuf[3] = 't';
	sbuf[4] = 'l';
	sbuf[5] = 'y';
	sbuf[6] = ' ';
	sbuf[7] = 'C';
	sbuf[8] = 'l';
	sbuf[9] = 'o';
	sbuf[10] = 'u';
	sbuf[11] = 'd';
	sbuf[12] = 'y';
	sbuf[13] = '\0';
	return sbuf;
}

char* SerialAPI::getWeather_low(uint8_t day) {
	sbuf[0] = '1';
	sbuf[1] = '0';
	sbuf[2] = '\0';
	return sbuf;
}

char* SerialAPI::getWeather_high(uint8_t day) {
	sbuf[0] = '2';
	sbuf[1] = '1';
	sbuf[2] = '\0';
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

