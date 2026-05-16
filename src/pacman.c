#include "pacman.h"
#include <string.h>
#include <stdio.h>
#include "utils.h"


void to_string(pacman_t* pacman, char* buffer, size_t buffer_size) {
    snprintf(buffer, buffer_size, "Pacman struct :\nname: %s\nname_cmd: %s\nupdate_cmd: %s\nupgrade_cmd: %s\nclean_orphans_cmd: %s\nclean_cache_cmd: %s",
        pacman->name, pacman->name_cmd, pacman->update_cmd, pacman->upgrade_cmd, pacman->clean_orphans_cmd, pacman->clean_cache_cmd);
}

