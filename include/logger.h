/*
 * Copyright 2025 Nicolas Spijkerman
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#if DEBUG

#define LOG_TRACE(module, format, ...) logger_log(TRACE_LEVEL, (module), (format), ##__VA_ARGS__)
#define LOG_DEBUG(module, format, ...) logger_log(DEBUG_LEVEL, (module), (format), ##__VA_ARGS__)
#define LOG_INFO(module, format, ...) logger_log(INFO_LEVEL, (module), (format), ##__VA_ARGS__)
#define LOG_WARN(module, format, ...) logger_log(WARN_LEVEL, (module), (format), ##__VA_ARGS__)
#define LOG_ERROR(module, format, ...) logger_log(ERROR_LEVEL, (module), (format), ##__VA_ARGS__)
#define LOG_FATAL(module, format, ...) logger_log(FATAL_LEVEL, (module), (format), ##__VA_ARGS__)

typedef enum {
    TRACE_LEVEL,
    DEBUG_LEVEL,
    INFO_LEVEL,
    WARN_LEVEL,
    ERROR_LEVEL,
    FATAL_LEVEL
} LOG_LEVEL;

int logger_init();
void logger_log(LOG_LEVEL level, const char *module, const char *format, ...);
void logger_close(void);

#else

#define LOG_TRACE(module, format, ...) ((void)0)
#define LOG_DEBUG(module, format, ...) ((void)0)
#define LOG_INFO(module, format, ...) ((void)0)
#define LOG_WARN(module, format, ...) ((void)0)
#define LOG_ERROR(module, format, ...) ((void)0)
#define LOG_FATAL(module, format, ...) ((void)0)

#endif
