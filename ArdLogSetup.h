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
#ifndef ARD_LOG_DEFSETUP_H
#define ARD_LOG_DEFSETUP_H

/** Logs free RAM if it has changed on every log_cycle() call. */
#define LOG_FREE_RAM false

/** Enables logger so that it can log over serial port. */
#define ENABLE_LOGGER true

/** Enables log on Debug level. */
#define LOG false

/** Enables logging in LED Clock. */
#define LOG_LC false

/** Enables logging in LED Display. */
#define LOG_D false

/** Enables log on Trace level. */
#define TRACE false

/** Log full time, or shorter version */
#define LOG_FULL_TIME false
#define LOG_SHORT_TIME true

/** log time. When off, time will not be logged at all. */
#define LOG_TIME true

/** Enable logs(....) and logc(...) functions. */
#define LOGS true

/**
 * True will get current time on each call on log(), otherwise we will get one sample for each log_cycle() and
 * in this case all messages within single cycle will have the same timestamp.
 */
#define USE_CURRENT_TIME false

/**
 * 4 serial hardware ports are supported: 1,2,3. If all are set to false we will use default Serial.
 */
#define USE_SERIAL_1 false
#define USE_SERIAL_2 false
#define USE_SERIAL_3 false

/** Buffer size for sprintf-template passed as first argument to log method. */
const static uint8_t PGBUF_SIZE = 64;

/** Buffer size for created message. */
const static uint8_t SBUF_SIZE = 96;

const static uint32_t SERIAL_SPEED = 115200;

#endif /* ARD_LOG_DEFSETUP_H */
