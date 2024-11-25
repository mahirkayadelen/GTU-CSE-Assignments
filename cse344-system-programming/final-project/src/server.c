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

#define BUFFER_SIZE 1024

void download_files(int client_sock, const char* client_dir) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received;

    // Receive the file count from the client
    int file_count;
    recv(client_sock, &file_count, sizeof(file_count), 0);

    // Receive each file from the client
    for (int i = 0; i < file_count; i++) {
        // Receive file name
        memset(buffer, 0, BUFFER_SIZE);
        bytes_received = recv(client_sock, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_received < 0) {
            perror("[-]Error receiving file name from client");
            close(client_sock);
            exit(1);
        }

        // Create file path
        char file_path[PATH_MAX];
        snprintf(file_path, PATH_MAX, "%s/%s", client_dir, buffer);

        // Open file for writing
        FILE* file_to_save = fopen(file_path, "wb");
        if (file_to_save == NULL) {
            perror("[-]Error opening file for writing on server");
            close(client_sock);
            exit(1);
        }

        // Receive file contents and write to file
        memset(buffer, 0, BUFFER_SIZE);
        while ((bytes_received = recv(client_sock, buffer, BUFFER_SIZE, 0)) > 0) {
            if (fwrite(buffer, sizeof(char), bytes_received, file_to_save) != bytes_received) {
                perror("[-]Error writing to file on server");
                fclose(file_to_save);
                close(client_sock);
                exit(1);
            }
            memset(buffer, 0, BUFFER_SIZE);
        }

        fclose(file_to_save);
        printf("Received file: %s\n", file_path);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        printf("Usage: %s <serverdir> <threadpool> <port>\n", argv[0]);
        return 1;
    }

    const char* server_dir = argv[1];
    // Ensure server directory exists
    struct stat st = {0};
    if (stat(server_dir, &st) == -1) {
        if (mkdir(server_dir, 0700) == -1) {
            perror("Error creating destination directory");
        }
    }


    int thread_pool_size = atoi(argv[2]);
    int port = atoi(argv[3]);

    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    // Create server socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("[-]Socket error");
        exit(1);
    }
    printf("[+]TCP server socket created.\n");

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind server socket to the specified port
    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("[-]Bind error");
        exit(1);
    }
    printf("[+]Bind to port %d.\n", port);

    // Listen for client connections
    if (listen(server_sock, thread_pool_size) < 0) {
        perror("[-]Listen error");
        exit(1);
    }
    printf("[+]Listening for incoming connections...\n");

    // Accept client connections and handle them
    while (1) {
        // Accept client connection
        client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_addr_len);
        if (client_sock < 0) {
            perror("[-]Accept error");
            exit(1);
        }

        printf("[+]Client connected: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        // Download files from the client
        download_files(client_sock, server_dir);

        printf("[+]All files received successfully.\n");

        close(client_sock);
    }

    close(server_sock);
server_addr.sin_addr.s_addr = inet_addr("10.8.24.241");
    return 0;
}
