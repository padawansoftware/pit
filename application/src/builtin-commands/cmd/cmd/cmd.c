#include <string.h>
#include <errno.h>
#include <stdbool.h>

#include "core.h"
#include "common/command.h"
#include "common/common.h"
#include "common/directory.h"
#include "common/error.h"
#include "array.h"
#include "argv.h"

int list_cmd();
int add_cmd();
int edit_cmd();
int rm_cmd();

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

struct argv* parsed_argv;
char* argv_options = "q";

// Turn off error when parsing non defined options
int opterr = 0;

bool quiet;

int main(int argc, char** argv) {
    parsed_argv = argv_parse(argc, argv, argv_options);
    quiet = argv_has_option(parsed_argv, 'q');

    if (array_length(parsed_argv->arguments)) {
        char* subcommandName = array_shift(parsed_argv->arguments);
        cmd *subcommand = get_command(subcommandName, subcommands);
        if(subcommand && init()) {

            subcommand->run();

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

int list_cmd() {
    printd(get_command_dir());

    return 0;
}

int add_cmd() {
    char* commandName,
        * cmdPath;

    if (array_length(parsed_argv->arguments) == 1) {
         commandName= argv_get_argument(parsed_argv, 0);
         cmdPath = get_command_path(commandName);

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

int edit_cmd() {
    char* commandName,
        * cmdPath;

    if (array_length(parsed_argv->arguments) == 1) {
        commandName = argv_get_argument(parsed_argv, 0);
        cmdPath = get_command_path(commandName);

        if (file_exists(cmdPath) == true) {
            char*openCmd;
            asprintf(&openCmd, "editor %s", cmdPath);
            system(openCmd);

            return 0;
        } else if (! quiet){
            e_error(UNKNOWN_CMD_E);
        }
    } else {
        error(INVALID_NUM_ARGS_E);
        e_error(USAGE);
    }
}

int rm_cmd() {
    char* commandName,
        * cmdPath;

    if(array_length(parsed_argv->arguments) == 1) {
        commandName = argv_get_argument(parsed_argv, 0);
        cmdPath = get_command_path(commandName);

        if (file_exists(cmdPath) == true) {
            remove_file(cmdPath);
        } else if (! quiet){
            e_error(UNKNOWN_CMD_E);
        }
    } else {
        error(INVALID_NUM_ARGS_E);
        e_error(USAGE);
    }
}