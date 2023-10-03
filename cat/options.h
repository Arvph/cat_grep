#ifndef OPTIONS_H
#define OPTIONS_H

#include <stdio.h>
#include <string.h>

void match(char* keys, FILE* myfile);
int line_count(FILE* myfile);
int func_b(char* buffer, int num, int num_s);
void func_e(char* buffer, int lin_num, int lines, int num_s);
int func_n(char* buffer, int num, int num_s);
int func_s(char* buffer, int tmp);
void func_t(char* str);



#endif