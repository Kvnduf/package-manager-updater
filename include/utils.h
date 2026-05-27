#ifndef UTILS_H
#define UTILS_H
#include <stddef.h>

void secure_free(void* ptr);

int secure_strncpy(char *dest, const char *src, size_t dest_size);

char* read_file(const char* file_path);

#endif // UTILS_H
