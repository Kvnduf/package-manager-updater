#include "pacman_reader.h"

#include <stdio.h>
#include "cJSON.h"
#include "utils.h"
#include <string.h>


static int read_pacman_from_json_item(const cJSON* json, pacman_t* pacman) {
    const cJSON* name = cJSON_GetObjectItem(json, NAME);
    const cJSON* nameCmd = cJSON_GetObjectItem(json, NAME_CMD);
    const cJSON* upgradeCmd = cJSON_GetObjectItem(json, UPGRADE_CMD);
    const cJSON* cleanOrphansCmd = cJSON_GetObjectItem(json, CLEAN_ORPHANS_CMD);
    const cJSON* cleanCacheCmd = cJSON_GetObjectItem(json, CLEAN_CACHE_CMD);

    init_pacman(pacman);

    if (cJSON_IsString(name)) set_name(pacman, name->valuestring);
    else return 1;

    if (cJSON_IsString(nameCmd)) set_name_cmd(pacman, nameCmd->valuestring);
    else return 1;

    if (cJSON_IsString(upgradeCmd)) set_upgrade_cmd(pacman, upgradeCmd->valuestring);
    else return 1;

    if (cJSON_IsString(cleanOrphansCmd)) set_clean_orphans_cmd(pacman, cleanOrphansCmd->valuestring);
    else return 1;

    if (cJSON_IsString(cleanCacheCmd)) set_clean_cache_cmd(pacman, cleanCacheCmd->valuestring);
    else return 1;

    return 0;
}

int read_pacmans_from_file(const char* file_path, pacman_t pacmans[], size_t* nb_pacmans) {
    int res = 0;
    char* json_str = NULL;
    cJSON* json = NULL;

    json_str = read_file(file_path);
    if (json_str == NULL) {
        res = -1;
        goto cleanup;
    }
    json = cJSON_Parse(json_str);

    if (!json) {
        res = -1;
        goto cleanup;
    }

    if (!cJSON_IsArray(json)) {
        res = 1;
        goto cleanup;
    }

    *nb_pacmans = 0;
    cJSON* item = NULL;
    cJSON_ArrayForEach(item, json) {
        if (!cJSON_IsObject(item)) {
            res = 1;
            goto cleanup;
        }
        if (*nb_pacmans >= MAX_PACMANS) {
            res = 2;
            goto cleanup;
        }
        if (read_pacman_from_json_item(item, pacmans + *nb_pacmans) != 0) {
            res = 1;
            goto cleanup;
        }
        (*nb_pacmans)++;
    }

cleanup:
    secure_free(json_str);
    if (json != NULL) cJSON_Delete(json);
    return res;
}

