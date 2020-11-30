#ifndef COMMANDLINE_H
#define COMMANDLINE_H
#include <stdio.h>

int strcmp(char const s1[],char const s2[]);

int flag_finder(char * cmdline[],char flag[],int num_args);

double convert_double(char const input[],double default_value);

void flag_checker (char *cmdline[],double flag[],int flag_index,int size);

FILE * open_file (char const name[]);

void read_and_print (FILE * file,FILE * output,int cmd_arg,char * cmdline[]);




#endif
