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

int read_file(const char *path, char **buffer) {
    if (!path || !buffer) {
        return EXIT_FAILURE;
    }
    *buffer = NULL;

    FILE *file = fopen(path, "rb");
    if (!file) {
        printf("Error: Failed to open file '%s' for reading\n", path);
        printf("Please check that the file exists and you have read permissions\n");
        return EXIT_FAILURE;
    }

    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        printf("Error: Failed to seek to end of file '%s'\n", path);
        return EXIT_FAILURE;
    }

    const long sz = ftell(file);
    if (sz < 0) {
        fclose(file);
        printf("Error: Failed to determine size of file '%s'\n", path);
        return EXIT_FAILURE;
    }
    rewind(file);

    *buffer = malloc((size_t) sz + 1);
    if (!*buffer) {
        fclose(file);
        printf("Error: Failed to allocate memory (%ld bytes) for file '%s'\n", sz + 1, path);
        return EXIT_FAILURE;
    }

    const size_t size = fread(buffer, 1, (size_t) sz, file);
    fclose(file);
    if (size != (size_t) sz) {
        free(buffer);
        printf("Error: Failed to read file '%s' (read %zu of %ld bytes)\n", path, size, sz);
        return EXIT_FAILURE;
    }

    *buffer[size] = '\0';
    return EXIT_SUCCESS;
}

int write_file(const char *path, const char *buffer) {
    if (!path || !buffer) {
        return EXIT_FAILURE;
    }

    FILE *file = fopen(path, "w");
    if (!file) {
        printf("Error: Failed to open file '%s' for writing\n", path);
        printf("Please check that you have write permissions for this location\n");
        return EXIT_FAILURE;
    }

    fputs(buffer, file);
    fclose(file);
    return EXIT_SUCCESS;
}
