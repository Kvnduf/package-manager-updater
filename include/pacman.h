#ifndef __PACMAN__H__
#define __PACMAN__H__
#include <stddef.h>

#define PACMAN_NAME_MAX 32
#define PACMAN_MAX_LINE_LENGTH 256

/**
 * @brief Struct representing a package manager with its name and associated commands.
 * 
 */
typedef struct {
   char name[PACMAN_NAME_MAX];
   char name_cmd[PACMAN_MAX_LINE_LENGTH];
   char update_cmd[PACMAN_MAX_LINE_LENGTH];
   char upgrade_cmd[PACMAN_MAX_LINE_LENGTH];
   char clean_orphans_cmd[PACMAN_MAX_LINE_LENGTH];
   char clean_cache_cmd[PACMAN_MAX_LINE_LENGTH];
} pacman_t;


void to_string(pacman_t* pacman, char* buffer, size_t buffer_size);


#endif // __PACMAN__H__

