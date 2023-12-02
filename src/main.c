#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command.h"

#define ARG_MAX 20

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
    char command[PATH_MAX];
    char **args = malloc(ARG_MAX * sizeof(char *));

    do {
        // Input
        printf("❯ ");
        if (!get_input(input)) {
            continue;
        }

        // Allocate space for the arguments
        args = realloc(args, ARG_MAX * sizeof(char *));
        
        parse_command(input, args);
        
        /*
        printf("Args:\n");
        for (int i = 0; args[i] != NULL; ++i) {
            printf("    %d: %s\n", i + 1, args[i]);
        }*/

    } while (execute_command(args));

    free(args);

    return EXIT_SUCCESS;
}
