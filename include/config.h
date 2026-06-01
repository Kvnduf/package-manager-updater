#ifndef CONFIG_H
#define CONFIG_H


#define MAX_PATH_LENGTH 512
#define MAX_COMMAND_LENGTH 256

#define CONFIG_DIRNAME "package-manager-updater"
#define PACMANS_FILENAME "pacmans.json"

#define FILE_SEP "/"

/**
 * @brief Get the config dir path object
 * @param buffer the buffer to fill with the config dir path, must be at least MAX_PATH_LENGTH bytes long
 * @return int  0 if success, -1 if an error occurred
 */
int get_config_dir_path(char buffer[MAX_PATH_LENGTH]);

/**
 * @brief Get the path from config dir object
 * 
 * @param filename  the name of the file in the config dir
 * @param buffer  the buffer to fill with the path, must be at least MAX_PATH_LENGTH bytes long
 * @return int  0 if success, -1 if an error occurred
 */
int get_path_from_config_dir(const char* filename, char buffer[MAX_PATH_LENGTH]);

#endif // CONFIG_H

