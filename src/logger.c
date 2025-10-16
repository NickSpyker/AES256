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

#if DEBUG

#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>

static FILE *log_file = NULL;

static const char *level_strings[] = {
    "TRACE",
    "DEBUG",
    "INFO",
    "WARN",
    "ERROR",
    "FATAL"
};

int logger_init() {
    time_t now;
    time(&now);
    const struct tm *time_info = localtime(&now);

    char filename[128];
    strftime(filename, sizeof(filename), "aes256_%y-%m-%d_%H-%M.log", time_info);

    log_file = fopen(filename, "w");
    if (log_file == NULL) {
        return 1;
    }

    return 0;
}

void logger_log(const LOG_LEVEL level, const char *module, const char *format, ...) {
    if (log_file == NULL) {
        return;
    }

    time_t now;
    time(&now);
    const struct tm *time_info = localtime(&now);

    char timestamp[32];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", time_info);

    fprintf(log_file, "[%s] [%s] [%s] ", timestamp, level_strings[level], module);

    va_list args;
    va_start(args, format);
    vfprintf(log_file, format, args);
    va_end(args);

    fprintf(log_file, "\n");
    fflush(log_file);
}

void logger_close(void) {
    if (log_file != NULL) {
        fclose(log_file);
        log_file = NULL;
    }
}

#endif
