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

    char temp[sizeof(char) * strlen(string)];
    strcpy(temp, string);

    char *token = strtok(temp, " ");
    strcpy(command, token);

    for (int x = 0; token; x++) {
        args[x] = token;
        token = strtok(NULL, " ");
    }
}

void execute_command(char path[], char *const args[], bool *running) {
    // Spawns a fork which executes the program at "path" with arguments
    // "args". If the program results in the termination of the shell,
    // "running" will be set to 0.

    if (!strcmp(path, "exit") || !strcmp(path, "quit")) {
        *running = 0;
        return;
    }

    // Spawn fork
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork error");
        return;

    } else if (pid == 0) {

        // Execute builtins
        if (!strcmp(path, "cd")) {
            printf("Changing to %s\n", args[1]);
            if (chdir(args[1]) < 0) {
                perror("CD error");
                return;
            };

            // Execute from PATH
        } else if (execvp(path, args) < 0) {
            perror("Execl error");
            return;
        }

    } else {
        // Wait for fork to finish
        int status;
        if (waitpid(pid, &status, 0) < 0) {
            perror("Waitpid error");
            return;
        }
    }

    return;
}
