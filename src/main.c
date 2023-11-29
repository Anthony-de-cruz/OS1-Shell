#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define INP_MAX 1000

void parse_command(char string[], char command[], char **args) {
    // Breaks down input "string" and modifies "command" and "args"
    // with the pieces.
    //

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

int get_current_dir(char *cwd) {

    if (getcwd(cwd, sizeof(cwd)) != NULL) {

        char *directories[INP_MAX];

        char temp[sizeof(char) * strlen(cwd)];
        strcpy(temp, cwd);

        char *token = strtok(temp, " ");
        for (int x = 0; token; x++) {
            directories[x] = token;
            token = strtok(NULL, " ");
        }

        int len = (int)sizeof(directories) / sizeof(char);
        cwd = directories[len - 1];
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {

    char input[INP_MAX];

    char cwd[PATH_MAX];
    get_current_dir(cwd);
    printf("%s\n", cwd);



    int running = 1;

    while (running) {

        // Input
        printf("\n%s>", cwd);
        if (fgets(input, sizeof(input), stdin) != NULL) {
            if (!strcmp(input, "\n")) {
                continue;
            }
            size_t len = strlen(input);
            if (len > 0 && input[len - 1] == '\n') {
                input[len - 1] = '\0';
            }
        } else {
            printf("Error reading input.\n");
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
