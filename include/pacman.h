#ifndef PACMAN_H
#define PACMAN_H
#include <stddef.h>

#define PACMAN_NAME_MAX 32
#define PACMAN_MAX_LINE_LENGTH 256

/**
 * @brief Struct representing a package manager with its name and associated commands.
 * 
 */


typedef enum {
   PACMAN_NAME,
   PACMAN_NAME_CMD,
   PACMAN_UPGRADE_CMD,
   PACMAN_CLEAN_ORPHANS_CMD,
   PACMAN_CLEAN_CACHE_CMD,
   
   PACMAN_NB_FIELDS
} pacman_field_t;

typedef struct {
   char fields[PACMAN_NB_FIELDS][PACMAN_MAX_LINE_LENGTH];
} pacman_t;

void pacman_init(pacman_t* pacman);

int pacman_set_field(pacman_t* pacman, pacman_field_t field, const char* value);

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

