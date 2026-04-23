#ifndef SHELL_H
#define SHELL_H

/** HEADERS */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/** PROTOTYPES */
extern char **environ;
void free_string_array(char **arr, int size);
void print_env(char **env);
void prompt(char *prompt);
char **str_to_arr(char *string);
char *_getenv(char *name);
int run_command(char **argv, char **args, int arglen, char **env, int l_stat);
int search_path(char **file, int overwrite);
int array_length(char **arr);
char *cmd_tok(char *line, char **savepnt);
int validate_command(char **argv, char **args, int arglen);
int shell_read(char **line, size_t *len);
int shell_exit(char **argv, char **args, int arglen, int l_stat);

#endif
