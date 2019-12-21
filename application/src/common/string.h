#ifndef _STRING_H_
#define _STRING_H_

/**
 * Allocate and return a formated string
 *
 * @param format The format of the returned string
 * @param ... variable number of params to be pased to the format
 *
 * @return char* The formated string
 */
char* rasprintf(const char* format, ...);

/**
 * Join an array of strings in a single array using *glue* as separator
 *
 * @param glue The character used to join the parts
 * @param parts An array of strings to be joined
 * @pram partsc The lenght of partsc
 *
 * @return char* The string with all parts joined
 */
char* implode(char* glue, char** parts, int partsc);

#endif