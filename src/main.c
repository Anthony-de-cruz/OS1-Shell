#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void parse_command(char string[], char command[], char **args) {

    char temp[sizeof(char) * strlen(string)];
    strcpy(temp, string);

    char *token = strtok(temp, " ");
    strcpy(command, token);

    for (int x = 0; token; x++) {
        args[x] = token;
        token = strtok(NULL, " ");
    }
}

void execute_command(char path[], char *const args[], int *running) {

    if (!strcmp(path, "exit") || !strcmp(path, "quit")) {
        *running = 0;
        return;
    }

    char *const arg[5] = {"ls", "/", NULL};

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

int main(int argc, char *argv[]) {

    char input[1000];

    char cwd[5];

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("CWD: %s\n", cwd);
    }

    int running = 1;

    while (running) {

        // Input
        printf("\n>");
        fgets(input, sizeof(input), stdin);
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }

        // char *argss[] = calloc(sizeof(char) * 100);
        char **args = calloc(100, sizeof(char));
        char command[100];

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
