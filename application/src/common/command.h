#ifndef _COMMAND_H_
#define _COMMAND_H_

typedef struct cmd_struct {
    // command name
    char *name;

    // function to invoque
    int (*run)();

    // function to init the command
    int (*init)(void);
} cmd;

/**
 * Find and return a command by name from an array of commands
 *
 * @param name Command name
 * @param commands An array of commands
 *
 * @return cmd*|NULL A pointer to the command if exists or NULL either
 */
cmd* get_command(const char name[], cmd* commands);

/**
 * Get command dir path
 *
 * @param dir Command directory name
 * @return commandDir Command directory path
 *
 */
char* _get_command_dir(const char directory[]);

/**
 *  Create builtin command directory if it does not exists
 *
 *  @param Command directory name
 *  @return commandDir Command directory path
 */
char* _create_command_dir(const char directory[]);

#define get_command_dir() _get_command_dir(CMD_DIR)
#define create_command_dir() _create_command_dir(CMD_DIR)

#endif

