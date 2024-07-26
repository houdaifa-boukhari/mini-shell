#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

void print_exit_status(int status) {
    if (WIFEXITED(status)) {
        int exit_code = WEXITSTATUS(status);
        printf("Process exited with status: %d\n", exit_code);
    } else if (WIFSIGNALED(status)) {
        int signal_number = WTERMSIG(status);
        printf("Process terminated by signal: %d (%s)\n", signal_number, strsignal(signal_number));
        printf("Exit status: %d\n", signal_number + 128);
    } else if (WIFSTOPPED(status)) {
        int signal_number = WSTOPSIG(status);
        printf("Process stopped by signal: %d (%s)\n", signal_number, strsignal(signal_number));
    } else if (WIFCONTINUED(status)) {
        printf("Process continued\n");
    } else {
        printf("Unknown status: %d\n", status);
    }
}

int main(int argc, char *argv[], char *envp[]) {
    pid_t pid;
    int status;
    char command[256];
    char *args[10];
    char *token;
    int i;

    while (1) {
        printf("my_shell> ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0; // Remove newline character

        // Tokenize the command string into arguments
        i = 0;
        token = strtok(command, " ");
        while (token != NULL && i < 9) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL; // Null-terminate the arguments array

        if (i == 0) continue; // If no command is entered, continue the loop

        if ((pid = fork()) == 0) {
            // Child process
            execve(args[0], args, envp);
            perror("execve");
            exit(errno); // Exit with errno to match typical shell behavior
        } else if (pid > 0) {
            // Parent process
            if (wait(&status) == pid) {
                print_exit_status(status);
            } else {
                perror("wait");
            }
        } else {
            perror("fork");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
