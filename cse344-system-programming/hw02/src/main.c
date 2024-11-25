#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include<time.h>
#include<fcntl.h>
#include<signal.h>
#include<sys/signal.h>
#include<sys/types.h>

char line[1024]; // Used it in main and signal_handler because of that global.

volatile sig_atomic_t keep_running = 1; // for signal handling and main(if any stop signal receives it will become 0)

#define MAX_COMMANDS 20

void signal_handler(int sig) {
    switch (sig) {
        case SIGINT:
        case SIGTERM:
        case SIGTSTP:
        case SIGQUIT:
            printf("\nCaught signal %d. Type ':q' to quit.\n", sig);
            fflush(stdout); // make sure the prompt is displayed before clearing the buffer
            fgets(line, sizeof(line), stdin); // wait for input directly from the user
            if (strcmp(line, ":q\n") == 0) {
                printf("Exiting...\n");
                keep_running = 0;
            } else {
                // clear the buffer and continue the loop
                line[0] = '\0';
                keep_running = 1;
            }
            break;
        default:
            printf("\nCaught signal %d. Returning to the prompt.\n", sig);
    }
}
void run_commands(int n, char *commands[], int pipefd[]);

int main() {
    char *args[256];
    int pipefd[2 * (MAX_COMMANDS - 1)];
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    // install signal handlers
    if (sigaction(SIGTERM, &sa, NULL) == -1) {
        perror("sigaction SIGTERM");
        exit(EXIT_FAILURE);
    }
    if (sigaction(SIGTSTP, &sa, NULL) == -1) {
        perror("sigaction SIGTSTP");
        exit(EXIT_FAILURE);
    }
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction SIGINT");
        exit(EXIT_FAILURE);
    }
    if (sigaction(SIGQUIT, &sa, NULL) == -1) {
        perror("sigaction SIGINT");
        exit(EXIT_FAILURE);
    }
    printf("Use :q to exit the program.\n");
    printf("Example usage: cat file1 > file2 OR ls | cat file2.txt | sort file2.txt < file3.txt\n");
    while (keep_running) {
        printf("myterminal> ");
        // read user input
        fgets(line, 1024, stdin);
        // split the input into separate commands
        int i = 0;
        char *token = strtok(line, "|\n");
        while (token != NULL) {
            if (strcmp(token, ":q") == 0) {
                keep_running = 0;
                return 1;
            }
            else{
                keep_running = 1;
            }
            args[i++] = token;
            token = strtok(NULL, "|\n");
        }
        args[i] = NULL;
        // create the required number of pipes
        for (int j = 0; j < i - 1; j++) {
            if (pipe(pipefd + 2 * j) == -1) {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
        }
        // run the commands
        run_commands(i, args, pipefd);
        // close all pipes
        for (int j = 0; j < 2 * (i - 1); j++) {
            close(pipefd[j]);
        }
        // wait for all child processes to finish
        for (int j = 0; j < i; j++) {
            wait(NULL);
        }
        // log the child process pids and corresponding commands
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        char filename[32];
        strftime(filename, 32, "log_%Y%m%d_%H%M%S.txt", tm);
        FILE *fp = fopen(filename, "w");
        if (fp == NULL) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < i; j++) {
            fprintf(fp, "pid=%d command=%s\n", getpid(), args[j]);
        }
        fclose(fp);
    }

    return 0;
}

void run_commands(int n, char *commands[], int pipefd[]) {
    for (int i = 0; i < n; i++) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // parse command arguments to look for input/output redirection
            char *cmd_args[256];
            char *token = strtok(commands[i], " \t\n");
            int j = 0;
            while (token != NULL) {
                if (strcmp(token, "<") == 0) {
                    // input redirection
                    token = strtok(NULL, " \t\n");
                    int fd = open(token, O_RDONLY);
                    if (fd == -1) {
                        perror("open");
                        exit(EXIT_FAILURE);
                    }
                    dup2(fd, STDIN_FILENO);
                    close(fd);
                } else if (strcmp(token, ">") == 0) {
                    // output redirection
                    token = strtok(NULL, " \t\n");
                    int fd = open(token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    if (fd == -1) {
                        perror("open");
                        exit(EXIT_FAILURE);
                    }
                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                } else {
                    cmd_args[j++] = token;
                }
                token = strtok(NULL, " \t\n");
            }
            cmd_args[j] = NULL;
            if (i > 0) {
                // redirect stdin to the previous pipe's read end
                dup2(pipefd[2 * (i - 1)], STDIN_FILENO);
            }
            if (i < n - 1) {
                // redirect stdout to the current pipe's write end
                dup2(pipefd[2 * i + 1], STDOUT_FILENO);
            }
            // close all pipe ends
            for (int j = 0; j < 2 * (n - 1); j++) {
                close(pipefd[j]);
            }
            // execute the command
            execvp(cmd_args[0], cmd_args);
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    }
}