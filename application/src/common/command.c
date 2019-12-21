#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "common/directory.h"
#include "common/command.h"
#include "common/common.h"
#include "common/string.h"
#include "common/error.h"

cmd* get_command(const char name[], cmd* commands)
{
    for (cmd* command = commands; command->name != NULL; command++) {
        if (!strcmp(name, command->name))
            return command;
    };

    return NULL;
}

char* _get_command_dir(const char directory[])
{
    return rasprintf("%s/%s/%s", getenv("HOME"), PIT_DIR , directory);
}

char* _create_command_dir(const char directory[])
{
    // Get command dir
    char *commandDir = _get_command_dir(directory);

    // Create command dir if it does not exists
    if (dir_exists(commandDir) != true) {
        if(_create_dir(commandDir) != 0) {
            e_error(UNEXP_E);
        }
    }

    return commandDir;
}