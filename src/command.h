#ifndef COMMAND_COMMAND_H
#define COMMAND_COMMAND_H

#include <stdbool.h>

// Parses input down into args
void parse_command(char input[], char *args[]);

// Spawns a fork which executes the program at "path" with arguments
// "args". If the program results in the termination of the shell,
// "running" will be set to 0.
bool execute_command(char *const args[]);

#endif
