#include <string.h>
#include <errno.h>
#include <stdbool.h>

#include "core.h"
#include "common/command.h"
#include "common/common.h"
#include "common/directory.h"
#include "common/error.h"


int list_cmd(int argc, char** argv);
int add_cmd(int argc, char** argv);
int edit_cmd(int argc, char** argv);
int rm_cmd(int argc, char** argv);

bool init(void);

#define USAGE "usage: pit cmd <options>\n" \
        "\n" \
        "The cmd command let define some commands\n" \
        "\n" \
        "<options>\n" \
        "\tlist <cmd>   List all commands\n" \
        "\tadd <cmd>    Add a command\n" \
        "\tedit <cmd>   Edit a command\n" \
        "\trm <cmd>     Remove a command\n"

// Subcommands
static cmd subcommands[] = {
    { "list", list_cmd },
    { "add", add_cmd },
    { "edit", edit_cmd },
    { "rm", rm_cmd },
    {0}
};

int main(int argc, char** argv) {
    if (--argc) {
        cmd *subcommand = get_command((++argv)[0], subcommands);
        if(subcommand && init()) {
            subcommand->run(--argc, ++argv);

            return errno;
        }
        e_error(UNKNOWN_CMD_E);
    }

    e_error(USAGE);
}

bool init(void) {
    create_command_dir();

    return true;
}


//Subcommmands

int list_cmd(int argc, char** argv) {
    printd(get_command_dir());

    return 0;
}

int add_cmd(int argc, char** argv) {
    if (argc == 1) {
        char*cmdPath = get_command_path(argv[0]);

        // Create the file for storing the command
        if (create_file(cmdPath) == 0) {
            char*openCmd;
            asprintf(&openCmd, "editor %s", cmdPath);
            system(openCmd);
            chmod(cmdPath, 0750);

            return 0;
        } else {
            e_error(UNEXP_E);
        }

    } else {
        error(INVALID_NUM_ARGS_E);
        e_error(USAGE);
    }
}

int edit_cmd(int argc, char** argv) {
    if (argc == 1) {
        char*cmdPath = get_command_path(argv[0]);
        if (file_exists(cmdPath) == true) {
            char*openCmd;
            asprintf(&openCmd, "editor %s", cmdPath);
            system(openCmd);

            return 0;
        } else {
            e_error(UNKNOWN_CMD_E);
        }
    } else {
        error(INVALID_NUM_ARGS_E);
        e_error(USAGE);
    }
}

int rm_cmd(int argc, char** argv) {
    if(argc == 1) {
        char* cmdPath = get_command_path(argv[0]);

        if (file_exists(cmdPath) == true) {
            remove_file(cmdPath);
        } else {
            e_error(UNKNOWN_CMD_E);
        }
    } else {
        error(INVALID_NUM_ARGS_E);
        e_error(USAGE);
    }
}