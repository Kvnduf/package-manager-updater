#include "pacman.h"
#include <stdio.h>
#include "utils.h"

void pacman_init(pacman_t* pacman) {
    if (!pacman) return;
    for (int i = 0; i < PACMAN_NB_FIELDS; i++) {
        pacman->fields[i][0] = '\0';
    }
}

int pacman_set_field(pacman_t* pacman, pacman_field_t field, const char* value) {
    if (!pacman) return -1;
    if (field < 0 || field >= PACMAN_NB_FIELDS) return -1;
    return secure_strncpy(pacman->fields[field], value, sizeof(pacman->fields[field]));
}

int pacman_to_string(pacman_t* pacman, char* buffer, size_t buffer_size) {
    if (!pacman || !buffer || buffer_size == 0) return -1;
    int n = snprintf(buffer, buffer_size, "Pacman struct :\nname: %s\nnameCmd: %s\nupgradeCmd: %s\ncleanOrphansCmd: %s\ncleanCacheCmd: %s\n\n",
        pacman->fields[PACMAN_NAME], pacman->fields[PACMAN_NAME_CMD], pacman->fields[PACMAN_UPGRADE_CMD], pacman->fields[PACMAN_CLEAN_ORPHANS_CMD], pacman->fields[PACMAN_CLEAN_CACHE_CMD]);
    if (n < 0 || (size_t)n >= buffer_size) {
        buffer[0] = '\0';
        return -1;
    }
    return 0;
}

