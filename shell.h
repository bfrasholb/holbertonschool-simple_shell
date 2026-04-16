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
extern char **environ;
void free_string_array(char **arr, int size);
void print_env(char **env);
void prompt(char *prompt);
char **str_to_arr(char *string);
char *_getenv(char *name);
int shell(char **env, char *line);
int run_command(char **args, int arglen, char **env);
int search_path(char **file, int overwrite);
int array_length(char **arr);

#endif
