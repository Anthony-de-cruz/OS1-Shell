#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void parse_command(char string[], char command[], char *args[]) {
    // Breaks down input "string" and modifies "command" and "args"
    // with the pieces.
    //

    // Reset args to NULL
    for (int x = 0; x < sizeof(*args) / sizeof(char *); x++) {
        args[x] = NULL;
    }

    char temp[sizeof(char) * strlen(string)];
    strcpy(temp, string);

    char *token = strtok(temp, " ");
    strcpy(command, token);

    for (int x = 0; token; x++) {
        args[x] = token;
        token = strtok(NULL, " ");
    }


    printf("size of *args %ld\nsize of args \n", sizeof(**args));
}

bool execute_command(char path[], char *const args[]) {
    // Spawns a fork which executes the program at "path" with arguments
    // "args". If the program results in the termination of the shell,
    // "running" will be set to 0.

    if (!strcmp(path, "exit") || !strcmp(path, "quit")) {
        return false;
    }

    // Spawn fork
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork error");
        return true;

    } else if (pid == 0) {

        // Execute builtins
        if (!strcmp(path, "cd")) {
            printf("Changing to %s\n", args[1]);
            if (chdir(args[1]) < 0) {
                perror("CD error");
                return true;
            };

            // Execute from PATH
        } else if (execvp(path, args) < 0) {
            perror("Execl error");
            return true;
        }

    } else {
        // Wait for fork to finish
        int status;
        if (waitpid(pid, &status, 0) < 0) {
            perror("Waitpid error");
            return true;
        }
    }

    return true;
}
