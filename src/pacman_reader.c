#include "pacman_reader.h"
#include "cJSON.h"
#include "utils.h"


const char *const PACMAN_FIELDS[PACMAN_NB_FIELDS] = {
    [PACMAN_NAME] = "name",
    [PACMAN_NAME_CMD] = "nameCmd",
    [PACMAN_UPGRADE_CMD] = "upgradeCmd",
    [PACMAN_CLEAN_ORPHANS_CMD] = "cleanOrphansCmd",
    [PACMAN_CLEAN_CACHE_CMD] = "cleanCacheCmd"
};

static int read_pacman_from_json_item(const cJSON* json, pacman_t* pacman) {
    if (!json || !pacman) return -1;

    cJSON* field = NULL;
    for (int i = 0; i < PACMAN_NB_FIELDS; i++) {
        field = cJSON_GetObjectItemCaseSensitive(json, PACMAN_FIELDS[i]);
        if (!field || !cJSON_IsString(field)) return 1;
        if (pacman_set_field(pacman, i, field->valuestring) != 0) return -1;
    }

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

