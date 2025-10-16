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

typedef enum {
    CMD_HELP,
    CMD_VERSION,
    CMD_ENCRYPT,
    CMD_DECRYPT
} CLI_COMMAND;

typedef struct {
    CLI_COMMAND cmd;
    char *key;
    char *msg;
    char *input_file;
    char *output_file;
} cli_options;

void cli_print_help();
void cli_print_version();

int cli_parse(int argc, const char *argv[], cli_options *opts);
