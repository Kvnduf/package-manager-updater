
#include "utils.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>


inline void secure_free(void* ptr) {
    if (ptr != NULL) free(ptr);
}

int secure_strncpy(char *dest, const char *src, size_t dest_size) {
    if (!dest || !src || dest_size == 0) return -1;

    strncpy(dest, src, dest_size - 1);
    dest[dest_size - 1] = '\0';
    return 0;
}

