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
#include "TempSensor.h"

TempSensor::TempSensor() :
		curentTemp(0), lastProbeTime(0), oneWire(DIG_PIN_TEMP_SENSOR), dallasTemperature(&oneWire) {
	dallasTemperature.begin();
	readTemp();
}

float TempSensor::getTemp() {
	return curentTemp;
}

void TempSensor::cycle() {
	uint32_t millis = ms();
	if (millis - lastProbeTime < PROBE_FREQ_MS) {
		return;
	}
	lastProbeTime = millis;
	readTemp();

}

inline void TempSensor::readTemp() {
	dallasTemperature.requestTemperatures();
	curentTemp = dallasTemperature.getTempCByIndex(0) + 0.5;

#if LOG_LC
	char buffer[6];
	dtostrf(curentTemp, 5, 1, buffer);
	log(F("TS TMP %s"), buffer);
#endif

#if USE_FEHRENHEIT
	curentTemp = curentTemp * 1.8 + 32;
#endif
}
