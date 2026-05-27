#include "pacman_reader.h"
#include "cJSON.h"
#include "utils.h"


static int read_pacman_from_json_item(const cJSON* json, pacman_t* pacman) {
    if (!json || !pacman) return -1;
    const cJSON* name = cJSON_GetObjectItemCaseSensitive(json, PACMAN_NAME);
    const cJSON* nameCmd = cJSON_GetObjectItemCaseSensitive(json, PACMAN_NAME_CMD);
    const cJSON* upgradeCmd = cJSON_GetObjectItemCaseSensitive(json, PACMAN_UPGRADE_CMD);
    const cJSON* cleanOrphansCmd = cJSON_GetObjectItemCaseSensitive(json, PACMAN_CLEAN_ORPHANS_CMD);
    const cJSON* cleanCacheCmd = cJSON_GetObjectItemCaseSensitive(json, PACMAN_CLEAN_CACHE_CMD);

    pacman_init(pacman);

    if (cJSON_IsString(name)) pacman_set_name(pacman, name->valuestring);
    else return 1;

    if (cJSON_IsString(nameCmd)) pacman_set_name_cmd(pacman, nameCmd->valuestring);
    else return 1;

    if (cJSON_IsString(upgradeCmd)) pacman_set_upgrade_cmd(pacman, upgradeCmd->valuestring);
    else return 1;

    if (cJSON_IsString(cleanOrphansCmd)) pacman_set_clean_orphans_cmd(pacman, cleanOrphansCmd->valuestring);
    else return 1;

    if (cJSON_IsString(cleanCacheCmd)) pacman_set_clean_cache_cmd(pacman, cleanCacheCmd->valuestring);
    else return 1;

    return 0;
}

int read_pacmans_from_file(const char* file_path, pacman_t pacmans[], size_t* nb_pacmans) {
    if (!pacmans || !nb_pacmans || !file_path) return -1;
    *nb_pacmans = 0;
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
    safe_free(json_str);
    if (json != NULL) cJSON_Delete(json);
    return res;
}

