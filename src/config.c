#include "config.h"
#include <stdio.h>
#include <stdlib.h>

int get_config_dir_path(char buffer[]) {
    const char* home = getenv("HOME");
    if (home == NULL) return -1;
    snprintf(buffer, MAX_PATH_LENGTH, "%s%s%s%s%s", home, FILE_SEP, ".config", FILE_SEP, CONFIG_DIRNAME);
    return 0;
}

int get_path_from_config_dir(const char* filename, char buffer[]) {
    char config_dir[MAX_PATH_LENGTH];
    if (get_config_dir_path(config_dir) != 0) {
        return -1;
    }
    snprintf(buffer, MAX_PATH_LENGTH, "%s%s%s", config_dir, FILE_SEP, filename);
    return 0;
}

