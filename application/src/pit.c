#include "command.h"
#include "directory.h"
#include "common.h"
#include "error.h"

// Commands
#include "path.h"
#include "cmd.h"
#include "exec.h"

// Sytem Libraries
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

// Registered commands
static cmd commands[] = {
    {"path", path_cmd, path_init},
    {"cmd", cmd_cmd, cmd_init},
    {"exec", exec_cmd, exec_init},
    {0}
};

// Functions
void pit_usage(void);
void pit_init(void);


int main(int argc, char **argv) {
    if(argc > 1) {
        // Init pit
        pit_init();

        // Execute the command
        struct cmd_struct *command = getCommand(argv[1], commands);
        if (command && command->init()) {
            argc -= 2;
            argv += 2;
            command->run(argc, argv);

            return errno;
        }
    }

    pit_usage();
}

void pit_usage(void) {

    fprintf(stderr,
        "The pit command improves commands\n"
        "\n"
        "Usage: pit <command> [<options>...]\n"
        "\n"
        "<command>\n"
        "\tpath     Define paths for use inside pit\n"
        "\tcmd      Define commands to automate actions\n"
        "\texec     Execute a command defined\n"
    );
}

void pit_init(void) {
    // Init pit path
    asprintf(&PIT_PATH,"%s/%s", getenv("HOME"), PIT_DIR);

    // Create pit directory if it does not exists yet
    if (dir_exists(PIT_PATH) != true) {
        if (_create_dir(PIT_PATH) == -1) {
            char err[50];
            sprintf(err, "Can't create pit directory at %s", PIT_PATH);
            e_error(err);
        }
    }
}
