#include "cmd.h"
#include "directory.h"
#include "error.h"
#include "command.h"

#include <stdlib.h>

int exec_cmd(int argc, char **argv) {
    if (argc > 0) {
        // Look for command
        char *cmd = cmd_get_path(argv[0]);
        if(file_exists(cmd) == true) {
            system(cmd);
        } else {
            e_error(UNKNOWN_CMD_E);
        }

        return 0;
    }

    return 1;
}

int exec_init() {
    return cmd_init();
}

void exec_usage(void) {
    fprintf(stderr,
        "usage: pit exec <cmd>\n"
        "\n"
        "The exec command let execute commands\n"
    );
}
