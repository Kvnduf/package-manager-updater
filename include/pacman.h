#ifndef PACMAN_H
#define PACMAN_H
#include <stddef.h>
#include "config.h"

#define PACMAN_NAME_MAX 32

/**
 * @brief Struct representing a package manager with its name and associated commands.
 * 
 */



typedef enum {
   PACMAN_UPGRADE_CMD,
   PACMAN_CLEAN_ORPHANS_CMD,
   PACMAN_CLEAN_CACHE_CMD,
   
   PACMAN_NB_COMMAND
} pacman_command_t;

typedef struct {
   char name[PACMAN_NAME_MAX];
   char nameCmd[MAX_COMMAND_LENGTH];
   char commands[PACMAN_NB_COMMAND][MAX_COMMAND_LENGTH];
} pacman_t;

void pacman_init(pacman_t* pacman);

int pacman_set_name(pacman_t* pacman, const char* name);

int pacman_set_nameCmd(pacman_t* pacman, const char* value);

int pacman_set_command(pacman_t* pacman, pacman_command_t command, const char* value);

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

