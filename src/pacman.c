#include "pacman.h"
#include <string.h>
#include <stdio.h>
#include "utils.h"

void init_pacman(pacman_t* pacman) {
    pacman->name[0] = '\0';
    pacman->name_cmd[0] = '\0';
    pacman->upgrade_cmd[0] = '\0';
    pacman->clean_orphans_cmd[0] = '\0';
    pacman->clean_cache_cmd[0] = '\0';
}

int set_name(pacman_t* pacman, const char* name){
    return secure_strncpy(pacman->name, name, sizeof(pacman->name));
}
int set_name_cmd(pacman_t* pacman, const char* name_cmd){
    return secure_strncpy(pacman->name_cmd, name_cmd, sizeof(pacman->name_cmd));
}
int set_upgrade_cmd(pacman_t* pacman, const char* upgrade_cmd){
    return secure_strncpy(pacman->upgrade_cmd, upgrade_cmd, sizeof(pacman->upgrade_cmd));
}
int set_clean_orphans_cmd(pacman_t* pacman, const char* clean_orphans_cmd){
    return secure_strncpy(pacman->clean_orphans_cmd, clean_orphans_cmd, sizeof(pacman->clean_orphans_cmd));
}
int set_clean_cache_cmd(pacman_t* pacman, const char* clean_cache_cmd){
    return secure_strncpy(pacman->clean_cache_cmd, clean_cache_cmd, sizeof(pacman->clean_cache_cmd));
}

void pacman_to_string(pacman_t* pacman, char* buffer, size_t buffer_size) {
    snprintf(buffer, buffer_size, "Pacman struct :\nname: %s\nnameCmd: %s\nupgradeCmd: %s\ncleanOrphansCmd: %s\ncleanCacheCmd: %s\n\n",
        pacman->name, pacman->name_cmd, pacman->upgrade_cmd, pacman->clean_orphans_cmd, pacman->clean_cache_cmd);
}

