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
#ifndef TEMPSENSORDRIVER_H_
#define TEMPSENSORDRIVER_H_

#include "ScrollingText8x8.h"
#include "TempSensor.h"

class TempSensorDriver {
public:
	TempSensorDriver(ScrollingText8x8* text, TempSensor* sensor);
	virtual ~TempSensorDriver();

private:
	class TextListener: public ScrollingText8x8::Listener {

	public:
		TextListener(TempSensor* sensor);
		virtual ~TextListener();
		void onScrollEnd();
	private:
		TempSensor* sensor;
	};

	TextListener listener;
};

#endif /* TEMPSENSORDRIVER_H_ */
