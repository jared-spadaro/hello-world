#ifndef TRANSLATE_H
#define TRANSLATE_H
#include <stdio.h>

FILE * open_file(char const name[]);

void read_and_print(FILE * input, FILE * output,char orig,char mew, int cmd_arg);

#endif
