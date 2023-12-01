#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command.h"

#define ARG_MAX 1000

// Gets the command line user input with fgets.
// Strips the input of \n and replaces it with \0.
bool get_input(char input[]) {

    if (fgets(input, ARG_MAX, stdin) != NULL) {
        if (!strcmp(input, "\n")) {
            return false;
        }
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }
    } else {
        printf("Error reading input.\n");
        return false;
    }

    return true;
}

int main(int argc, char *argv[]) {

    char input[ARG_MAX];
    // char **args = calloc(PATH_MAX, sizeof(char));
    char *args[ARG_MAX];
    char command[PATH_MAX];

    bool running = true;

    while (running) {

        // Input
        printf("\n❯ ");
        if (!get_input(input)) {
            continue;
        }

        

        parse_command(input, command, args);

        printf("CMD: %s > %s %s %s %s\n", command, args[0], args[1], args[2],
               args[3]);

        running = execute_command(command, args);

        printf("Running1: %s\n", running ? "true" : "false");
    }

    return EXIT_SUCCESS;
}
