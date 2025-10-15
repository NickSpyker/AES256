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

#include "utils.h"
#include "aes.h"

const char *USAGE = {
    "AES256 - Advanced Encryption Standard 256-bit\n"
    "A command-line tool for encrypting and decrypting files using AES-256 encryption.\n"
    "\n"
    "USAGE:\n"
    "    aes256 [OPTIONS]\n"
    "    aes256 <COMMAND> <KEY> <INPUT_FILE> <OUTPUT_FILE>\n"
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
};

aes_config parse_args(const int argc, const char *argv[]) {
    if (argc < 2) {
        printf("%s\n", USAGE);
        exit(EXIT_FAILURE);
    }

    if (argc == 2) {
        const char *option = argv[1];

        if (!strcmp(option, "-h") || !strcmp(option, "--help")) {
            printf("%s\n", USAGE);
            exit(EXIT_SUCCESS);
        }
        if (!strcmp(option, "-v") || !strcmp(option, "--version")) {
            printf("0.1.0\n");
            exit(EXIT_SUCCESS);
        }

        printf("Error: Unknown option '%s'\n", option);
        printf("Use -h or --help for usage information\n");
        exit(EXIT_FAILURE);
    }

    if (argc != 5) {
        printf("Error: Invalid number of arguments (expected 4, got %d)\n", argc - 1);
        printf("Usage: aes256 <COMMAND> <KEY> <INPUT_FILE> <OUTPUT_FILE>\n");
        exit(EXIT_FAILURE);
    }

    const char *command = argv[1];
    AES_MODE mode;

    if (!strcmp(command, "e") || !strcmp(command, "encrypt")) {
        mode = Encrypt;
    } else if (!strcmp(command, "d") || !strcmp(command, "decrypt")) {
        mode = Decrypt;
    } else {
        printf("Error: Unknown command '%s'\n", command);
        printf("Valid commands are: encrypt (e), decrypt (d)\n");
        exit(EXIT_FAILURE);
    }

    const char *key = argv[2];

    const char *input_file = argv[3];
    const char *message = read_file_to_str(input_file);

    const aes_config config = {
        mode,
        (char *) key,
        (char *) message,
    };

    return config;
}
