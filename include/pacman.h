#ifndef PACMAN_H
#define PACMAN_H
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
   char upgrade_cmd[PACMAN_MAX_LINE_LENGTH];
   char clean_orphans_cmd[PACMAN_MAX_LINE_LENGTH];
   char clean_cache_cmd[PACMAN_MAX_LINE_LENGTH];
} pacman_t;

void pacman_init(pacman_t* pacman);

int pacman_set_name(pacman_t* pacman, const char* name);
int pacman_set_name_cmd(pacman_t* pacman, const char* name_cmd);
int pacman_set_upgrade_cmd(pacman_t* pacman, const char* upgrade_cmd);
int pacman_set_clean_orphans_cmd(pacman_t* pacman, const char* clean_orphans_cmd);
int pacman_set_clean_cache_cmd(pacman_t* pacman, const char* clean_cache_cmd);

/**
 * @brief Converts a pacman struct to a string representation and stores it in the provided buffer.
 * 
 * @param pacman  the pacman struct to convert
 * @param buffer  the buffer to store the string representation
 * @param buffer_size  the size of the buffer
 * @return int  0 on success, -1 on failure
 */
int pacman_to_string(pacman_t* pacman, char* buffer, size_t buffer_size);


#endif // PACMAN_H

