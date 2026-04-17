#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int btrtok(char **args, char *line);
char *get_path(char *cmd);
void execute(char **argv);

#endif