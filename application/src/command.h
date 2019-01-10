#ifndef _COMMAND_H_
#define _COMMAND_H_

typedef struct cmd_struct {
    // command name
    char *name;

    // function to invoque
    int (*run)(int, char **);

    // function to init the command
    int (*init)(void);
} cmd;

struct cmd_struct *getCommand(const char s[], cmd *commands);


#endif

