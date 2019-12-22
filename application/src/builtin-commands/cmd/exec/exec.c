#include <stdlib.h>

#include "core.h"
#include "common/command.h"
#include "common/directory.h"
#include "common/error.h"

#define USAGE "usage: pit exec <cmd>\n" \
        "\n" \
        "The exec command let execute commands\n" \

bool init();

int main(int argc, char** argv) {
    if (--argc && init()) {
        // Look for command
        char* cmd = get_command_path((++argv)[0]);

        if(file_exists(cmd) == true) {
            system(cmd);
        } else {
            e_error(UNKNOWN_CMD_E);
        }

        return 0;
    }

    return 1;
}

bool init() {
    return dir_exists(get_command_dir());
}