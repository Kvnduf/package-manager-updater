#ifndef __CONFIG__H__
#define __CONFIG__H__


#define MAX_PATH_LENGTH 512

#define CONFIG_DIRNAME "package-manager-updater"
#define PACMANS_FILENAME "pacmans.json"

#define FILE_SEP "/"

int get_config_dir_path(char buffer[]);

int get_path_from_config_dir(const char* filename, char buffer[]);

#endif // __CONFIG__H__

