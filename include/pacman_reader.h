#ifndef __PACMAN_READER__H__
#define __PACMAN_READER__H__

#include "pacman.h"
#include "config.h"

#define MAX_PACMANS 32

#define NAME "name"
#define NAME_CMD "nameCmd"
#define UPGRADE_CMD "upgradeCmd"
#define CLEAN_ORPHANS_CMD "cleanOrphansCmd"
#define CLEAN_CACHE_CMD "cleanCacheCmd"


/**
 * @brief reads pacmans from a json file with a specific format
 * 
 * @param file_path the path to the json file
 * @param pacmans  the array to fill with the pacmans read from the file
 * @param nb_pacmans  the number of pacmans read from the file
 * @return int 0 if success, 1 if an error occurred during parsing, 2 if the number of pacmans read exceeds MAX_PACMANS, -1 if an error occurred
 */
int read_pacmans_from_file(const char* file_path, pacman_t pacmans[], size_t* nb_pacmans);

#endif