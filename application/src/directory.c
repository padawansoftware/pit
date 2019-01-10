#include "common.h"
#include "error.h"
#include "directory.h"

#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Private functions
static int sort(const void *, const void*);


int dir_exists(const char path[]) {
    DIR* dir;
    if ((dir = opendir(path))) {
        closedir(dir);

        return true;
    }

    return errno;
}

int printd(const char path[]) {
    array *elements = ls(path);

    char *element;
    for (int i = 0; i < array_length(elements); i++) {
        element = array_get(elements, i);
        if (strcmp(".", element) && strcmp("..", element))
            printf("%s\t", element);
    }

    printf("\n");

    return 0;
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

int file_exists(const char path[]) {
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