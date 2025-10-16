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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cli.h"
#include "io.h"
#include "logger.h"

void cli_print_help() {
    printf(
        "AES256 - Advanced Encryption Standard 256-bit\n"
        "A command-line tool for encrypting and decrypting files using AES-256 encryption\n"
        "\n"
        "USAGE:\n"
        "    aes256 [OPTIONS]\n"
        "    aes256 [COMMAND] <KEY> <INPUT_FILE> <OUTPUT_FILE>\n"
        "\n"
        "OPTIONS:\n"
        "    -h, --help       Display this help message and exit\n"
        "    -v, --version    Display version information and exit\n"
        "\n"
        "COMMANDS:\n"
        "    encrypt, e       Encrypt the input file with the provided key\n"
        "    decrypt, d       Decrypt the input file with the provided key\n"
        "\n"
        "ARGUMENTS:\n"
        "    <KEY>            Encryption/decryption key (256-bit)\n"
        "    <INPUT_FILE>     Path to the file to encrypt or decrypt\n"
        "    <OUTPUT_FILE>    Path where the output will be saved\n"
    );
}

void cli_print_version() {
    printf("0.1.0\n");
}

int cli_parse(const int argc, const char *argv[], cli_options *opts) {
    if (argc < 2) {
        opts->cmd = CMD_HELP;
        LOG_INFO("cli_parse", "Command: print help");
        return EXIT_SUCCESS;
    }

    const char *cmd = argv[1];

    if (argc == 2) {
        if (!strcmp(cmd, "-h") || !strcmp(cmd, "--help")) {
            opts->cmd = CMD_HELP;
            LOG_INFO("cli_parse", "Command: print help");
            return EXIT_SUCCESS;
        }
        if (!strcmp(cmd, "-v") || !strcmp(cmd, "--version")) {
            opts->cmd = CMD_VERSION;
            LOG_INFO("cli_parse", "Command: print version");
            return EXIT_SUCCESS;
        }

        printf("Error: Unknown option '%s'\n", cmd);
        printf("Use -h or --help for usage information\n");
        LOG_ERROR("cli_parse", "Error: Unknown option '%s'\n", cmd);
        return EXIT_FAILURE;
    }

    if (argc != 5) {
        printf("Error: Invalid number of arguments (expected 4, got %d)\n", argc - 1);
        printf("Usage: aes256 <COMMAND> <KEY> <INPUT_FILE> <OUTPUT_FILE>\n");
        LOG_ERROR("cli_parse", "Error: Invalid number of arguments (expected 4, got %d)\n", argc - 1);
        return EXIT_FAILURE;
    }

    if (!strcmp(cmd, "e") || !strcmp(cmd, "encrypt")) {
        opts->cmd = CMD_ENCRYPT;
        LOG_INFO("cli_parse", "Command: encrypt");
    } else if (!strcmp(cmd, "d") || !strcmp(cmd, "decrypt")) {
        opts->cmd = CMD_DECRYPT;
        LOG_INFO("cli_parse", "Command: decrypt");
    } else {
        printf("Error: Unknown command '%s'\n", cmd);
        printf("Valid commands are: encrypt (e), decrypt (d)\n");
        LOG_ERROR("cli_parse", "Error: Unknown command '%s'\n", cmd);
        return EXIT_FAILURE;
    }

    opts->key = (char *) argv[2];

    const char *input_file = argv[3];

    char *buffer = NULL;
    if (!read_file(input_file, &buffer)) {
        return EXIT_FAILURE;
    }
    opts->msg = buffer;

    opts->input_file = (char *) input_file;
    opts->output_file = (char *) argv[4];

    return EXIT_SUCCESS;
}
