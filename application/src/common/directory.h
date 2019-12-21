#ifndef _DIRECTORY_H
#define _DIRECTORY_H

#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include "array.h"

void init_pit_directory(void);

/**
 *  @return
 *      true if directory exists
 *      false if directory does not exists
 */
bool dir_exists(const char path[]);

/**
 *  @return
 *      true if file_exists
 *      false if error or not existing file
 */
bool file_exists(const char path[]);

/**
 *  @return
 *      0 if success
 *      errno if error
 */
int create_file(const char path[]);

/**
 * Prints directory content
 *
 * @param path Path to the directory
 */
void printd(const char path[]);

/**
 * Get directory content
 *
 * @param path Path to the directory
 *
 * @return array* An array of char*, each one
 */
array* ls(const char path[]);

#define create_dir mkdir(path, mode);
#define _create_dir(path) mkdir(path, 0700)

#define remove_file(path) unlink(path)

/**
 *  Check @filename is a valid filename
 *  @return
 *      true if is a valid filename
 *      false if is a non-valid filenam
 */
#define is_valid_filename(filename) ! strchr(filename, '/')

#endif