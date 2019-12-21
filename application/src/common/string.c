#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

char* rasprintf(const char* format, ...)
{
    char* result;
    va_list arg;

    va_start (arg, format);
    vasprintf(&result, format, arg);
    va_end (arg);

    return result;
}

char* implode(char* glue, char** parts, int partsc)
{
    char *result, *tmp;

    if (partsc > 0) {
        result = (char *) parts[0];

        for (int i = 1; i < partsc; i++ ) {
            tmp = rasprintf("%s%s%s", result, glue, parts[i]);
            free(result);
            result = tmp;
        }

        free(tmp);

        return result;
    }

    return "";
}