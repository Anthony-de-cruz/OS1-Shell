#ifndef COMMAND_COMMAND_H
#define COMMAND_COMMAND_H

#include <stdbool.h>

void parse_command(char string[], char command[], char *args[]);

void execute_command(char path[], char *const args[], bool *running);

#endif
