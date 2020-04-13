#ifndef _ARGV_H_
#define _ARGV_H_

#include <stdbool.h>

#include "array.h"

/**
 * struct to hold parsed options from argv
 */
struct argv_option {
    char name;
    char* value;
};

/**
 * struct to hold parsed argv
 */
struct argv {
    array* arguments;
    array* options;
};

/**
 * Parse global argv input
 *
 * @param argc Number of input arguments passed to the program
 * @param argv Array containing all input arguments passed to the program
 * @param optstring An string with the options expected in the form required by getopt
 *
 * @return struct argv* The structure containing parsed argv
 */
struct argv* argv_parse(int argc, char** argv, char* optstring);

/**
 * Check whether an specific options has been passed as input argument
 *
 * @param arguments Parsed argv structure
 * @param option The word used to indicate the option to be checked
 *
 * @return bool Whether the option has or not been passed as input argument
 */
bool argv_has_option(struct argv* arguments, char option);

/**
 * Retrieve an option
 *
 * @param arguments Parsed argv structure
 * @param option The word used to indicate the option to be retrieved
 *
 * @return struct argv_option*|NULL The option required or NULL if it does not exists
 */
struct argv_option* argv_get_option (struct argv* arguments, char option);

/**
 * Check whether an specific argument has been passed as input argument
 *
 * @param arguments Parsed argv structure
 * @param option The argument to be checked
 *
 * @return bool Whether the argument has or not been passed as input argument
 */
bool argv_has_argument(struct argv* arguments, char* argument);

/**
 * Return an argument from argv
 *
 * @param arguments Parsed argv structure
 * @param argument Index of the argument to be retrieved in argv
 *
 * @return char* The argument in the position required or NULL if it does not exists any
 */
char* argv_get_argument(struct argv* arguments, int argument);

/**
 * Print argv content
 *
 * @param argv Parsed argv structure
 */
void argv_print(struct argv* argv);

#endif