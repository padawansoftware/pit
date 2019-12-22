#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <libgen.h>

#include "array.h"
#include "common/common.h"
#include "common/error.h"
#include "common/directory.h"

// Private functions
static int sort(const void *, const void*);

bool dir_exists(const char path[]) {
    DIR* dir;
    if ((dir = opendir(path))) {
        closedir(dir);

        return true;
    }

    return false;
}

bool file_exists(const char path[]) {
    FILE *file;
    if ((file = fopen(path, "r")))
    {
        fclose(file);

        return true;
    }

    return false;
}

int create_file(const char path[]) {
    FILE *file;
    if(file = fopen(path, "a+")) {
        fclose(file);

        return 0;
    }

    return errno;
}

void printd(const char path[]) {
    array *elements = ls(path);

    char *element;
    for (int i = 0; i < array_length(elements); i++) {
        element = array_get(elements, i);
        if (strcmp(".", element) && strcmp("..", element))
            printf("%s\t", element);
    }

    printf("\n");
}

array* ls(const char path[]) {
    DIR *dir;
    struct dirent *d;
    array *elements;

     if (dir = opendir(path)) {
        elements = array_init();
        while ((d = readdir(dir)) != NULL)
        {
            array_push(elements, d->d_name);
        }
        closedir(dir);
    }

    array_sort(elements, sort);

    return elements;
}

static int sort(const void *a, const void *b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

char * get_bin_path()
{
    char* buff = calloc(100, sizeof(char));

    readlink("/proc/self/exe", buff, 100);

    return buff;
}

char* get_bin_dir()
{
    return dirname(get_bin_path());
}