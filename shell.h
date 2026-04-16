#ifndef SHELL_H
#define SHELL_H

/** HEADERS */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>

/** PROTOTYPES */
void free_string_array(char **arr, int size);
char **str_to_arr(char *string);
int search_path(char **file, int overwrite);

#endif
