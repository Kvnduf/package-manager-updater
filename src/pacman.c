#include "pacman.h"
#include <stdio.h>
#include "utils.h"

void pacman_init(pacman_t* pacman) {
    if (!pacman) return;
    pacman->name[0] = '\0';
    pacman->name_cmd[0] = '\0';
    pacman->upgrade_cmd[0] = '\0';
    pacman->clean_orphans_cmd[0] = '\0';
    pacman->clean_cache_cmd[0] = '\0';
}

int pacman_set_name(pacman_t* pacman, const char* name){
    if (!pacman) return -1;
    return secure_strncpy(pacman->name, name, sizeof(pacman->name));
}
int pacman_set_name_cmd(pacman_t* pacman, const char* name_cmd){
    if (!pacman) return -1;
    return secure_strncpy(pacman->name_cmd, name_cmd, sizeof(pacman->name_cmd));
}
int pacman_set_upgrade_cmd(pacman_t* pacman, const char* upgrade_cmd){
    if (!pacman) return -1;
    return secure_strncpy(pacman->upgrade_cmd, upgrade_cmd, sizeof(pacman->upgrade_cmd));
}
int pacman_set_clean_orphans_cmd(pacman_t* pacman, const char* clean_orphans_cmd){
    if (!pacman) return -1;
    return secure_strncpy(pacman->clean_orphans_cmd, clean_orphans_cmd, sizeof(pacman->clean_orphans_cmd));
}
int pacman_set_clean_cache_cmd(pacman_t* pacman, const char* clean_cache_cmd){
    if (!pacman) return -1;
    return secure_strncpy(pacman->clean_cache_cmd, clean_cache_cmd, sizeof(pacman->clean_cache_cmd));
}

int pacman_to_string(pacman_t* pacman, char* buffer, size_t buffer_size) {
    if (!pacman || !buffer || buffer_size == 0) return -1;
    int n = snprintf(buffer, buffer_size, "Pacman struct :\nname: %s\nnameCmd: %s\nupgradeCmd: %s\ncleanOrphansCmd: %s\ncleanCacheCmd: %s\n\n",
        pacman->name, pacman->name_cmd, pacman->upgrade_cmd, pacman->clean_orphans_cmd, pacman->clean_cache_cmd);
    if (n < 0 || (size_t)n >= buffer_size) {
        buffer[0] = '\0';
        return -1;
    }
    return 0;
}

