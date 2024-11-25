#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>

void upload_directory(const char* client_dir) {
    // Fork a child process to execute the rsync command
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        // Use execlp to execute the rsync command
        execlp("rsync", "rsync", "-r", "--delete", client_dir, ".", NULL);

        // execlp will only return if an error occurs
        perror("[-]Error executing rsync");
        exit(1);
    } else if (pid > 0) {
        // Parent process
        // Wait for the child process to complete
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            // Check the exit status of the child process
            int exit_status = WEXITSTATUS(status);

            if (exit_status == 0) {
                printf("[+]Directory synchronized successfully.\n");
            } else {
                printf("[-]Failed to synchronize directory.\n");
            }
        } else {
            printf("[-]Child process terminated abnormally.\n");
        }
    } else {
        perror("[-]Fork error");
        exit(1);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: %s <clientdir> <port>\n", argv[0]);
        return 1;
    }

    const char* client_dir = argv[1];
    // Ensure client directory exists
    struct stat st = {0};
    if (stat(client_dir, &st) == -1) {
        if (mkdir(client_dir, 0700) == -1) {
            perror("Error creating destination directory");
        }
    }

    
    int port = atoi(argv[2]);

    int client_sock;
    struct sockaddr_in server_addr;

    // Create client socket
    client_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (client_sock < 0) {
        perror("[-]Socket error");
        exit(1);
    }
    printf("[+]TCP client socket created.\n");

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to the server
    if (connect(client_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("[-]Connection error");
        exit(1);
    }
    printf("[+]Connected to the server.\n");

    // Synchronize directories
    upload_directory(client_dir);

    


    close(client_sock);
server_addr.sin_addr.s_addr = inet_addr("10.8.24.241");

    return 0;
}
