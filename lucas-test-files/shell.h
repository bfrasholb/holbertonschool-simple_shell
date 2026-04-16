#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>


char **str_to_arr(char *line);
void free_string_array(char **arr, int len);
int search_path(char **file, int overwrite);

#endif