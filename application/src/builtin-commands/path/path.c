#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <errno.h>
#include <dirent.h>
#include <getopt.h>
#include <string.h>
#include <stdbool.h>

#include "common/common.h"
#include "common/command.h"
#include "common/directory.h"
#include "common/error.h"
#include "common/string.h"
#include "array.h"
#include "argv.h"

typedef struct str_path {
    // path name
    char name[128];

    // path
    char path[256];
} path;

int list_path();
int find_path();
int add_path();
int edit_path();
int remove_path();

bool init(void);
array* get_all_paths(void);
char* get_path_filepath(char path[]);
int get_max_length(array *paths);
int save_path(path* p);
path* retrieve_path(char pathName[]);
static int sortByName(const void *a, const void *b);
void print_paths(array *paths, bool fullName);
void rm_by_pathName(char* pathName);
void rm_path(path* p);

#define CMD_DIR "paths"
#define UNEXISTING_PATH_E "Unexisting path"
#define EXISTING_PATH_E  "Path already exists"
#define USAGE "usage: pit path <options>\n" \
        "\n" \
        "The path command let define some paths for pit\n" \
        "\n" \
        "<options>\n" \
        "\tlist                     List all paths defined\n" \
        "\tfind <path_name>         Return the path for <path_name>\n" \
        "\tadd <path_name> <path>   Add a new <path> to pit with name <path_name>\n" \
        "\tedit <path_name> <path>  Changes the <path> named <path_name>\n" \
        "\trm <path_name>           Remove the path defined as <path_name>\n"

// Subcommands
static cmd subcommands[] = {
        { "list", list_path },
        { "find", find_path },
        { "add", add_path },
        { "edit", edit_path },
        { "rm", remove_path },
        { 0 }
};

struct argv* parsed_argv;
char* argv_options = "nq";

bool quiet;

int main (int argc, char **argv)
{
    cmd* subcommand;
    char* commandName;

    parsed_argv = argv_parse(argc, argv, argv_options);
    quiet = argv_has_option(parsed_argv, 'q');

    if (array_length(parsed_argv->arguments)) {
        commandName = array_shift(parsed_argv->arguments);
        subcommand = get_command(commandName, subcommands);
        if (subcommand) {
            if (init()) {

                return subcommand->run();
            }

            e_error(UNEXP_E);
        }

        e_error(UNKNOWN_CMD_E);
    }

    e_error(USAGE);
}

bool init(void)
{
    create_command_dir();

    return true;
}

// Subcommands
int list_path()
{
    bool nameOnly = false;
    array *paths;

    nameOnly = argv_has_option(parsed_argv, 'n');

    paths = get_all_paths();
    array_sort(paths, sortByName);
    print_paths(paths, nameOnly);

    return 0;
};

int find_path()
{
    char* pathName;
    path* p;

    if (array_length(parsed_argv->arguments) == 1) {
        pathName = argv_get_argument(parsed_argv, 0);

        if ((p = retrieve_path(pathName)) != NULL) {
            printf("%s\n", p->path);
        } else if (! quiet) {
            e_error(UNEXISTING_PATH_E);
        }
    } else {
        error(INVALID_NUM_ARGS_E);
        e_error(USAGE);
    }

    return 0;
}

int add_path()
{
    char* pathName,
        * pathPath;
    path p;

    if(array_length(parsed_argv->arguments) == 2) {
        pathName = argv_get_argument(parsed_argv, 0);
        pathPath = argv_get_argument(parsed_argv, 1);

        // Check path does not already exist
        if (retrieve_path(pathName) == NULL) {
            strcpy(p.name, pathName);
            strcpy(p.path, realpath(pathPath, NULL));

            save_path(&p);
        } else if (! quiet) {
            e_error(EXISTING_PATH_E);
        }
    } else {
        error(INVALID_NUM_ARGS_E);
        e_error(USAGE);
    }

    return 0;
}

int edit_path()
{
    char* pathName, * pathPath;
    path* p;

    if (array_length(parsed_argv->arguments)) {
        pathName = argv_get_argument(parsed_argv, 0);
        pathPath = argv_get_argument(parsed_argv, 1);;

        // Check path exists
        if ((p = retrieve_path(pathName)) != NULL) {
            strcpy(p->path, pathPath);

            save_path(p);
        } else if (! quiet) {
            e_error(UNEXISTING_PATH_E);
        }

        return 0;
    } else {

        e_error(INVALID_NUM_ARGS_E "\n" USAGE);
    }
}

int remove_path()
{
    char* pathName;

    if (array_length(parsed_argv->arguments)) {
        pathName = argv_get_argument(parsed_argv, 0);
        rm_by_pathName(pathName);
    } else {
        e_error(INVALID_NUM_ARGS_E "\n" USAGE);
    }

    return 0;
}


// Help functions

/**
 * Stores a path in disk
 *
 * @param p The path to be stored
 *
 * @return int
 *      0 if success
 *      1 otherwise
 */
int save_path(path* p)
{
    FILE *pathFile;

    char *pathFilePath = get_path_filepath(p->name);
    if ((pathFile= fopen(pathFilePath, "w")) != NULL) {
        fputs(p->path, pathFile);
        fclose(pathFile);

        return 0;
    }

    e_error(UNEXP_E);
}

/**
 * Find a path in disk
 *
 * @param name The path nam
 *
 * @return path*|null The path finded or NULL
 */
path* retrieve_path(char pathName[])
{
    char *pathFilePath;
    FILE *pathFile;
    path *p;

    pathFilePath = get_path_filepath(pathName);
    if (pathFilePath != NULL) {
        if (file_exists(pathFilePath)) {
            if ((pathFile = fopen(pathFilePath, "r"))) {
                p = malloc(sizeof(path));
                strcpy(p->name, pathName);
                fgets(p->path, 128, pathFile);

                fclose(pathFile);

                return p;
            }
        }
    }

    return NULL;
}

/**
 * Get the full filepath for a given path name
 *
 * @param pathName Name of the path
 *
 * @return char* Full filepath
 */
char* get_path_filepath(char *pathName)
{
    if (is_valid_filename(pathName) == true) {
        return rasprintf("%s/%s", get_command_dir(), pathName);
    }

    return NULL;
}

/**
 * Removes a path from disk
 *
 * @param p The path to be removed from disk
 */
void rm_path(path* p)
{
    rm_by_pathName(p->name);
}

/**
 * Removes a path from disk by pathname
 *
 * @param pathName Pathname of the path to be removed
 */
void rm_by_pathName(char* pathName)
{
    char *pathFilepath = get_path_filepath(pathName);

    if (file_exists(pathFilepath) == true) {
        remove_file(pathFilepath);
    } else if (! quiet){
        e_error(UNEXISTING_PATH_E);
    }
}

/**
 * Retrieve all paths from disk
 *
 * @return array* The array of paths retrieved from disk
 */
array* get_all_paths(void)
{
    path* p;
    DIR* dir;
    struct dirent* d;
    char* pathFilePath;
    FILE* pathFile;
    array* paths;

    paths = array_init();
    if (dir = opendir(get_command_dir())) {
        // Read paths directory
        while ((d = readdir(dir)) != NULL) {
            // Special files . & .. are not required
            if (strcmp(d->d_name, ".") && strcmp(d->d_name, "..")){
                p = malloc(sizeof(path));
                strcpy(p->name, d->d_name);
                pathFilePath = get_path_filepath(p->name);

                // Read pathfile
                if ((pathFile = fopen(pathFilePath, "r")) != NULL) {
                    fgets(p->path, 128, pathFile);
                    array_push(paths, p);

                    fclose(pathFile);
                }
            }
        }
        closedir(dir);
    }

    return paths;
}

static int sortByName(const void *a, const void *b)
{
    return strcmp((*(const path**)a)->name, (*(const path**)b)->name);
}

/**
 * Return the maximum length pathname from an arrray of paths
 *
 * @param paths The array of paths to be checked
 *
 * @return int The maximum length pathname
 */
int get_pathname_max_length(array* paths)
{
    int maxLength = 0;
    path *p;

    for (int i = 0; i < paths->length; i++ ) {
        p = array_get(paths, i);
        if (strlen(p->name) > maxLength) {
            maxLength = strlen(p->name);
        }
    }

    return maxLength;
}

/**
 * Prints and array of paths
 *
 * @param paths An array of paths to be printed
 * @param nameOnly Whether print the name and the path or just the name
 */
void print_paths(array* paths, bool nameOnly)
{
    path *p;
    int align;

    align = (get_pathname_max_length(paths) + 8) / 8 * 8;
    for (int i = 0; i < paths->length; i ++) {
        p = array_get(paths, i);
        if (nameOnly) {
            printf("%s\t", p->name);
        } else {
            printf("%-*s%s\n", align, p->name, p->path);
        }
    }

    if (nameOnly) {
        printf("\n");
    }
}