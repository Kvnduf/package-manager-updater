#ifndef __UTILS__H__
#define __UTILS__H__
#include <stddef.h>

void secure_free(void* ptr);

int secure_strncpy(char *dest, const char *src, size_t dest_size);

#endif // __UTILS__H__
