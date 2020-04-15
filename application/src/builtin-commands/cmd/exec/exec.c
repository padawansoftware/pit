#include <stdlib.h>

#include "core.h"
#include "common/command.h"
#include "common/directory.h"
#include "common/error.h"
#include "argv.h"

#define USAGE "usage: pit exec <cmd>\n" \
        "\n" \
        "The exec command let execute commands\n" \

bool init();

struct argv* parsed_argv;
char* argv_options = "q";

bool quiet;

int main(int argc, char** argv) {
    char* commandName,
        * commandPath;

    parsed_argv = argv_parse(argc, argv, argv_options);
    quiet = argv_has_option(parsed_argv, 'q');
    if (--argc && init()) {
        commandName = argv_get_argument(parsed_argv, 0);
        commandPath = get_command_path(commandName);

        if(file_exists(commandPath) == true) {
            system(commandPath);
        } else if (! quiet) {
            e_error(UNKNOWN_CMD_E);
        }

        return 0;
    }

    return 1;
}

bool init() {
    return dir_exists(get_command_dir());
}