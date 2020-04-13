#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "argv.h"
#include "array.h"

static struct argv* argv_init()
{
    struct argv* argv = malloc(sizeof(struct argv));

    argv->arguments = array_init();
    argv->options = array_init();

    return argv;
}

static int argv_add_option(struct argv* argv, char name, char* value)
{
    struct argv_option* option = malloc(sizeof(struct argv_option));

    option->name = name;
    option->value = value;

    array_push(argv->options, option);

    return 0;
}

static int argv_add_argument(struct argv* argv, char* argument)
{
    array_push(argv->arguments, argument);

    return 0;
}

struct argv* argv_parse(int argc, char** argv, char* optstring)
{
    int opt;
    struct argv* str_argv = argv_init();

    // Parse options
    while ((opt = getopt(argc, argv, optstring)) != -1) {
        switch (opt) {
            case '?':
                break;
            default:
                argv_add_option(str_argv, opt, optarg);
                break;
        }
    }
    // Parse arguments
    for (int i = 0; i < argc - optind; i++) {
        argv_add_argument(str_argv, argv[optind + i]);
    }
    return str_argv;
}

bool argv_has_option(struct argv* argv, char option)
{
    return !! argv_get_option(argv, option);
}

struct argv_option* argv_get_option(struct argv* argv, char option)
{
    array* options = argv->options;
    struct argv_option* str_option;

    for (int i = 0; i < array_length(options); i++) {
        if (option == (str_option = array_get(options, i))->name) {
            return str_option;
        }
    }

    return NULL;
}

bool argv_has_argument(struct argv* argv, char* argument)
{
    array* arguments = argv->arguments;

    for (int i = 0; i < array_length(arguments); i++) {
        if (! strcmp(argument, (char*) array_get(arguments, i))) {
            return true;
        }
    }

    return false;
}

char* argv_get_argument(struct argv* argv, int argument)
{
    return array_get(argv->arguments, argument);
}

void argv_print(struct argv* argv)
{
    //Print arguments
    printf("\n"
           "List arguments\n"
           "--------------\n"
    );
    for (int i = 0; i < array_length(argv->arguments); i++) {
        printf("%s\n", argv_get_argument(argv, i));
    }

    printf("\n"
           "List options\n"
           "--------------\n"
    );

    struct argv_option* o;
    for(int i = 0; i < array_length(argv->options); i++) {
        o = array_get(argv->options, i);
        printf("%c --> %s\n", o->name, o->value);
    }

    printf("\n");
}