
#include "utils.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


void secure_free(void* ptr) {
    if (ptr != NULL) free(ptr);
}

int secure_strncpy(char *dest, const char *src, size_t dest_size) {
    if (!dest || !src || dest_size == 0) return -1;

    strncpy(dest, src, dest_size - 1);
    dest[dest_size - 1] = '\0';
    return 0;
}


char* read_file(const char* file_path) {
    FILE* file = fopen(file_path, "r");
    if (!file) return NULL;

    if (0 != fseek(file, 0, SEEK_END)) {
        fclose(file);
        return NULL;
    }
    long length = ftell(file);
    if (length < 0) {
        fclose(file);
        return NULL;
    }
    if (0 != fseek(file, 0, SEEK_SET)) {
        fclose(file);
        return NULL;
    }

    char* buffer = malloc(length + 1);
    if (!buffer) {
        fclose(file);
        return NULL;
    }

    if (fread(buffer, 1, length, file) != (size_t)length) {
        free(buffer);
        fclose(file);
        return NULL;
    }
    buffer[length] = '\0';

    fclose(file);
    return buffer;
} 
