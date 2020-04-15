#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "common/string.h"
#include "common/common.h"
#include "common/error.h"
#include "common/directory.h"
#include "argv.h"
#include "array.h"

#define USAGE "The pit command improves commands\n" \
        "\n" \
        "Usage: pit <command> [<options>...]\n" \
        "\n" \
        "<command>\n" \
        "\tpath     Define paths for use inside pit\n" \
        "\tcmd      Define commands to automate actions\n" \
        "\texec     Execute a command defined\n" \

bool init();
int run_command();
bool command_exists(char* command);
char* get_command_path(char* command);

struct argv* parsed_argv;
char* argv_options = "";

// Turn off error when parsing non defined options
int opterr = 0;

int main(int argc, char** argv) {
    parsed_argv = argv_parse(argc, argv, argv_options);
    if (array_length(parsed_argv->arguments)) {
        init();

        return run_command();
    }

    e_error(USAGE);
}

bool init() {
    // Init pit path
    char* PIT_PATH = rasprintf("%s/%s", getenv("HOME"), PIT_DIR);

    // Create pit directory if it does not exists yet
    if (dir_exists(PIT_PATH) != true) {
        if (_create_dir(PIT_PATH) == -1) {
            e_error(rasprintf("Can't create pit directory at %s", PIT_PATH));
        }
    }

    return true;
}

/**
 * Execute a command
 */
int run_command()
{
    int result;

    char* command = argv_get_argument(parsed_argv, 0);
    char* commandPath = get_command_path(command);
    array_shift(parsed_argv->arguments);
    if (file_exists(commandPath)) {
        char* execCommand = rasprintf("%s %s", commandPath, implode(" ", (char**) parsed_argv->arguments->buffer, array_length(parsed_argv->arguments)));
        result = system(execCommand);
    } else {
        e_error(rasprintf("Command %s is not installed", command));
    }

    return WEXITSTATUS(result);
}

/**
 * Check if a command executable exists
 *
 * @param command The command name
 *
 * @return bool Whether the command executable exists or not
 */
bool command_exists(char* command)
{
    char* commandPath = get_command_path(command);

    return file_exists(commandPath);
}

/**
 * Get the path of the executable command
 *
 * @param command The command name
 *
 * @return char* The absolute path to the command
 */
char* get_command_path(char* command)
{
    return rasprintf("%s/pit-%s", get_bin_dir(), command);
}