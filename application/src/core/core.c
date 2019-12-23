#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "common/string.h"
#include "common/common.h"
#include "common/error.h"
#include "common/directory.h"

#define USAGE "The pit command improves commands\n" \
        "\n" \
        "Usage: pit <command> [<options>...]\n" \
        "\n" \
        "<command>\n" \
        "\tpath     Define paths for use inside pit\n" \
        "\tcmd      Define commands to automate actions\n" \
        "\texec     Execute a command defined\n" \

bool init(int argc, char** argv);
int run_command(char* command, char** arguments, int argumentsc);
bool command_exists(char* command);
char* get_command_path(char* command);

int main(int argc, char** argv) {
    if (--argc) {
        init(argc, argv);

        char* command = argv[1];
        char** arguments = argv + 2;

        return run_command(command, arguments, --argc);
    }

    e_error(USAGE);
}

bool init(int argc, char** argv) {
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
 *
 * @param command The command name
 * @param arguments The arguments passed to the command
 * @argumentsc The number of arguments passed
 *
 */
int run_command(char* command, char** arguments, int argumentsc)
{
    int result;
    char* commandPath = get_command_path(command);
    if (file_exists(commandPath)) {
        char* execCommand = rasprintf("%s %s", commandPath, implode(" ", arguments, argumentsc));
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