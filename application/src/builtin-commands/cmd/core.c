#include <stdio.h>

#include "core.h"
#include "common/string.h"
#include "common/directory.h"
#include "common/command.h"

char* get_command_path(char commandDirectoryName[]) {
    char* cmdPath;
    char* command;

    if (is_valid_filename(commandDirectoryName) == true) {
        return rasprintf("%s/%s", get_command_dir(), commandDirectoryName);
    }

    return NULL;
}
