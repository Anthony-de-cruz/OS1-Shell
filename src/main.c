#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command.h"

#define ARG_MAX 1000

bool get_input(char input[]) {
    // Gets the command line user input with fgets.
    // Strips the input of \n and replaces it with \0.

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
    char cwd[PATH_MAX];

    bool running = true;

    while (running) {

        // Input
        printf("\n❯ ");
        if (!get_input(input)) {
            continue;
        }

        char **args = calloc(PATH_MAX, sizeof(char));
        char command[PATH_MAX];

        parse_command(input, command, args);

        printf("CMD: %s > %s %s %s %s\n", command, args[0], args[1], args[2],
               args[3]);

        char *const argz[] = {"-a", NULL};
        execute_command(command, args, &running);

        if (!running) {
            free(args);
        }
    }

    return EXIT_SUCCESS;
}
