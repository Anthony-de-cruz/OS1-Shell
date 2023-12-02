#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

// Parses input down into args
void parse_command(char input[], char *args[]) {

    int i = 0;
    char *token = strtok(input, " ");

    // Tokenize the input string
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }

    // Set the last element of the array to NULL
    args[i] = NULL;
}

// Spawns a fork which executes the program at "path" with arguments
// "args". If the program results in the termination of the shell,
// "running" will be set to 0.
bool execute_command(char *const args[]) {

    // Execute builtins
    if (!strcmp(args[0], "exit") || !strcmp(args[0], "quit")) {
        return false;

    } else if (!strcmp(args[0], "cd")) {
        if (chdir(args[1]) < 0) {
            perror("CD error");
            return true;
        };
        return true;
    }

    // Spawn fork
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork error");
        return false;

        // If child fork
    } else if (pid == 0) {

        // Execute from PATH
        if (execvp(args[0], args) < 0) {
            perror("Execl error");
            return false;
        }
        return false;

    } else {
        // Wait for fork to finish
        int status;
        if (waitpid(pid, &status, 0) < 0) {
            perror("Waitpid error");
            return false;
        }
    }
    // Parent process exit point
    return true;
}
