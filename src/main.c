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

#include "cli.h"
#include "aes256.h"
#include "io.h"

int main(const int argc, const char *argv[]) {
    cli_options opts = {0};
    if (!cli_parse(argc, argv, &opts)) {
        return EXIT_FAILURE;
    }

    switch (opts.cmd) {
        case CMD_HELP:
            cli_print_help();
            return EXIT_SUCCESS;
        case CMD_VERSION:
            cli_print_version();
            return EXIT_SUCCESS;
        case CMD_ENCRYPT:
            if (!aes256_encrypt(opts.key, opts.msg)) {
                return EXIT_FAILURE;
            }
            return write_file(opts.output_file, opts.msg);
        case CMD_DECRYPT:
            if (!aes256_decrypt(opts.key, opts.msg)) {
                return EXIT_FAILURE;
            }
            return write_file(opts.output_file, opts.msg);
        default:
            cli_print_help();
            return EXIT_FAILURE;
    }
}
