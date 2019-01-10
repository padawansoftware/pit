#include "command.h"
#include <string.h>

/**
 * Find and retrun a command by name
 */
struct cmd_struct *getCommand(const char name[], cmd *commands)
{
    for (cmd *c = commands; c->name != NULL; c++) {
        if (!strcmp(name, c->name))
            return c;
    };

    return NULL;
}
