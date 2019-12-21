#ifndef _CORE_H_
#define _CORE_H_

#define CMD_DIR "cmd"

/**
 * Return the path to the command directory where the configuration is stored
 *
 * @param commandDirectoryName The name of the command directory
 *
 * @return char* The full path to the command directory (commands directory path + command directory name)
 */
char* get_command_path(char commandDirectoryName[]);

#endif
