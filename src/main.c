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
#include "logger.h"

int main(const int argc, const char *argv[]) {
#if DEBUG
    logger_init();
#endif
    LOG_TRACE("main", "Logger initialized");

    cli_options opts = {0};
    if (cli_parse(argc, argv, &opts)) {
        LOG_TRACE("main", "Exiting logger, failed to parse args, main exit code is 1");
#if DEBUG
        logger_close();
#endif
        return EXIT_FAILURE;
    }

    int exit_code = EXIT_SUCCESS;
    switch (opts.cmd) {
        case CMD_HELP:
            cli_print_help();
            break;
        case CMD_VERSION:
            cli_print_version();
            break;
        case CMD_ENCRYPT:
            if (aes256_encrypt(opts.key, opts.msg)) {
                exit_code = EXIT_FAILURE;
                break;
            }
            exit_code = write_file(opts.output_file, opts.msg);
            break;
        case CMD_DECRYPT:
            if (aes256_decrypt(opts.key, opts.msg)) {
                exit_code = EXIT_FAILURE;
                break;
            }
            exit_code = write_file(opts.output_file, opts.msg);
            break;
        default:
            cli_print_help();
            exit_code = EXIT_FAILURE;
            break;
    }

    LOG_TRACE("main", "Exiting logger, main exit code is %d", exit_code);
#if DEBUG
    logger_close();
#endif

    return exit_code;
}
