#ifndef SHELL_H
#define SHELL_H

void print_prompt1(void);
void print_prompt2(void);
void initsh(void);
char *read_cmd(void);

#include "source.h"
int  parse_and_execute(struct source_s *src);

/* shell builtin utilities */
int dump(int argc, char **argv);

struct builtin_s{
    char *name;                             //utility name, used to invoke the utility
    int (*func)(int argc, char **argv);   //func ptr to the func that implements the builtin utility in out shell
};;

//the list of builtin utilities
extern struct builtin_s builtins[];        

//and their count
extern int builtins_count;

#endif