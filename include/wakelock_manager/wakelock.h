#ifndef WAKELOCK_H
#define WAKELOCK_H
#include <stdbool.h>

#define MAX_WAKELOCK_NAME_LEN 32

typedef struct {
    char name[MAX_WAKELOCK_NAME_LEN];
    bool (*is_supported)(void);
    int (*acquire)(void);
    int (*release)(void);
} wakelock_t;

#endif // WAKELOCK_H
