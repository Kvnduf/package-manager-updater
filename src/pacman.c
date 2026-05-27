#include "pacman.h"
#include <stdio.h>
#include "utils.h"

void pacman_init(pacman_t* pacman) {
    if (!pacman) return;
    for (int i = 0; i < PACMAN_NB_COMMAND; i++) {
        pacman->commands[i][0] = '\0';
    }
}

int pacman_set_command(pacman_t* pacman, pacman_command_t command, const char* value) {
    if (!pacman) return -1;
    if (command < 0 || command >= PACMAN_NB_COMMAND) return -1;
    return secure_strncpy(pacman->commands[command], value, sizeof(pacman->commands[command]));
}

int pacman_to_string(pacman_t* pacman, char* buffer, size_t buffer_size) {
    if (!pacman || !buffer || buffer_size == 0) return -1;
    int n = snprintf(buffer, buffer_size, "Pacman struct :\nname: %s\nnameCmd: %s\nupgradeCmd: %s\ncleanOrphansCmd: %s\ncleanCacheCmd: %s\n\n",
        pacman->commands[PACMAN_NAME], pacman->commands[PACMAN_NAME_CMD], pacman->commands[PACMAN_UPGRADE_CMD], pacman->commands[PACMAN_CLEAN_ORPHANS_CMD], pacman->commands[PACMAN_CLEAN_CACHE_CMD]);
    if (n < 0 || (size_t)n >= buffer_size) {
        buffer[0] = '\0';
        return -1;
    }
    return 0;
}

