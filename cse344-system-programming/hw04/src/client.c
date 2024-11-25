#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <errno.h>

int fd_write_client;
int fd_read_client;
char client_fifo_write[100];

#define min(a,b) ((a) < (b) ? (a) : (b))

void handle_signal(int sig) {
    if(sig == SIGUSR2){
        printf("Server is shutting down. Terminating client.\n");
        exit(0);
    }
    else if(sig == SIGINT){
        char newcommand[100];
        sprintf(newcommand, "%d quit\n", getpid());
        if (write(fd_write_client, newcommand, strlen(newcommand)) == -1) { // let server know client exits
                    perror("Failed to send write request to server");
                    exit(1);
        }
        printf("\nBye..\n");

        // Close named pipe and exit
        close(fd_read_client);
        close(fd_write_client);
        exit(0);
    }
    else if(sig == SIGTSTP){
        printf("\nSIGTSTP is not allowed for client!\n If you want to quit , type 'quit'\n");
    }
}


void open_read_fifo(){
    // Open client FIFO for writing
    fd_read_client = open(client_fifo_write, O_RDONLY);
    if (fd_read_client == -1) {
        perror("Failed to open client FIFO for writing");
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <Connect/tryConnect> <ServerPID>\n", argv[0]);
        exit(1);
    }


    struct sigaction sa;
    sa.sa_handler = handle_signal; // a function to handle the server shutdown signal
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;  // Make sure SA_RESTART is not set
    if (sigaction(SIGUSR2, &sa, NULL) == -1) {
        perror("Failed to install signal handler");
        exit(1);
    }

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Failed to install signal handler");
        exit(1);
    }

    if (sigaction(SIGTSTP, &sa, NULL) == -1) {
        perror("Sigaction hatası");
        return 1;
    }

    pid_t server_pid = atoi(argv[2]);
    if (kill(server_pid, 0) == -1) { // for controlling server PID is already exist
        if (errno == ESRCH) {
            printf("Server process does not exist.\n");
            exit(1);
        } else {
            perror("Failed to send signal");
            exit(1);
        }
    }

    // Open named pipe for writing
    int fd_write;
    if (strcmp(argv[1], "Connect") == 0) {
        printf("Waiting for server queue...");
        fflush(stdout); // Flush the buffer to ensure immediate printing waiting.
        while ((fd_write = open("/tmp/my_named_pipe_read", O_WRONLY)) == -1) {
            printf("Failed to connect to server.\n");
            exit(1);
        }

    } else if (strcmp(argv[1], "tryConnect") == 0) {
        fd_write = open("/tmp/my_named_pipe_read", O_WRONLY | O_NONBLOCK);
        if (fd_write == -1) {
            printf("Failed to connect to server.\n");
            exit(1);
        } else {

        }
    } else {
        printf("Invalid connection type. Use 'Connect' or 'tryConnect'.\n");
        exit(1);
    }

    // Open named pipe for reading
    int fd_read = open("/tmp/my_named_pipe_write", O_RDONLY);
    if (fd_read == -1) {
        perror("Failed to open named pipe for reading first");
        exit(1);
    }

    // Send connection request to server
    char request[256];
    memset(request, 0, sizeof(request));
    int pid = getpid();
    sprintf(request, "%d %s", pid,argv[1]);
    if (write(fd_write, request, strlen(request)) == -1) {
        perror("Failed to send connection request to server");
        exit(1);
    }


    char response[256];
    memset(response, 0, sizeof(response));
    // receive server connection response
    if (read(fd_read, response, sizeof(response)) == -1) {
        perror("Failed to read response from server");
        exit(1);
    }
    // if client connects with tryConnect, analysis response
    if(strcmp(argv[1],"tryConnect") == 0){
        if(strcmp(response,"Full") == 0){
            printf("Server is Full!\n");
            exit(1);
        }
    }

    // OPEN  CLIENT PID -NAMEDFIFOS 
    char client_fifo_read[100];
    sprintf(client_fifo_write, "/tmp/my_named_pipe_write_%d", getpid());

    sprintf(client_fifo_read, "/tmp/my_named_pipe_read_command");



    // Open client FIFO for reading
    fd_write_client = open(client_fifo_read, O_WRONLY | O_NONBLOCK);
    if (fd_write_client == -1) {
        printf("\nServer shutting down.\n");
        exit(1);
    }

    printf("Connection established.\n");

    // Handle commands
    while (1) {

        // Read command from user
        char command[256];

        printf(">>Enter command: ");
        
        fgets(command, sizeof(command), stdin);
        strtok(command, "\n");
        

        // Handle commands
        if (strcmp(command, "help") == 0) {
            printf("\tAvailable commands are:\n");
            printf("help, list, readF, writeT, upload, download, quit, killServer\n\n");
        } 
        else if (strcmp(command, "help list") == 0) {
            printf("  list       - Display the list of files in the server's directory.\n");
        }
        else if (strcmp(command, "help readF") == 0) {
            printf("Usage: readF <file> <line #>\nDisplay the #th line of the <file>, returns with an error if <file> does not exists\n");
        }
        else if (strcmp(command, "help writeT") == 0) {
            printf("Usage: writeT <file> <line #> <string>\nRequest to write the content of “string” to the #th line the <file>\n");
        }
        else if (strcmp(command, "help upload") == 0) {
            printf("Usage: upload <file>\nUploads the file from the current working directory of client to the Servers directory\n");
        }
        else if (strcmp(command, "help download") == 0) {
            printf("Usage: download <file>\nRequest to receive <file> from Servers directory to client side\n");
        }
        
        else if (strcmp(command, "list") == 0) {
            // Send request to server to list files
            char newcommand[100];
                sprintf(newcommand, "%d list\n", getpid());
            if (write(fd_write_client, newcommand, strlen(newcommand)) == -1) {
                perror("Failed to send list request to server");
                exit(1);
            }

            // Open client FIFO for writing
            open_read_fifo();

            // Wait for response from server
            char file_list[1024];
            memset(file_list, 0, sizeof(file_list));
            if (read(fd_read_client, file_list, sizeof(file_list)) == -1) {
                perror("Failed to read file list from server");
                exit(1);
            }
            printf("Files in server directory:\n%s", file_list);
            close(fd_read_client);
        } 

        else if (strncmp(command, "readF ", 6) == 0) {
            char request[512];
            snprintf(request, sizeof(request), "%d %s\n", getpid(),command);
            if (write(fd_write_client, request, strlen(request)) == -1) {
                perror("Failed to send read request to server");
                exit(1);
            }

            // Open client FIFO for writing
            open_read_fifo();

            long content_size;
            if (read(fd_read_client, &content_size, sizeof(content_size)) == -1) {
                perror("Failed to read content size from server");
                exit(1);
            }
            int bytes_read;
            long bytes_left = content_size;
            char file_content[1024];
            char buffer[1024];
            if(content_size == 2338328219396892998){ // this value means File is locked by another client.
                bytes_read = read(fd_read_client, buffer, 1024); // for cleaning PIPE buffer for avoid future program logic continue
                continue;
            }
            else if(content_size == 8367798494427701574){ // this value means there is no any file.
                printf("No file found matching this filename\n");
                bytes_read = read(fd_read_client, buffer, 1024); // for cleaning PIPE buffer for avoid future program logic continue
                continue;
            }
            printf("File content:\n");
            while (bytes_left > 0 && (bytes_read = read(fd_read_client, file_content, min(sizeof(file_content) - 1, bytes_left))) > 0) {
                file_content[bytes_read] = '\0';
                printf("%s", file_content);
                bytes_left -= bytes_read;
            }
            if (bytes_read == -1) {
                perror("Failed to read file content from server");
                exit(1);
            }
            printf("\n");
            close(fd_read_client);
        }

        else if (strncmp(command, "writeT ", 7) == 0) {
            char request[512];
            snprintf(request, sizeof(request), "%d %s\n", getpid(),command);
            if (write(fd_write_client, request, strlen(request)) == -1) {
                perror("Failed to send write request to server");
                exit(1);
            }


            // Open client FIFO for writing
            open_read_fifo();

            // Wait for response from server
            char server_response[512];
            memset(server_response, 0, sizeof(server_response));
            if (read(fd_read_client, server_response, sizeof(server_response)) == -1) {
                perror("Failed to read server response");
                exit(1);
            }
            printf("%s", server_response);
            close(fd_read_client);
        }

        else if (strncmp(command, "upload ", 7) == 0) {
            char request[512];
            snprintf(request, sizeof(request), "%d %s\n", getpid(),command);
            // Send the upload command and filename to the server
            if (write(fd_write_client, request, strlen(request)) == -1) {
                perror("Failed to send upload request to server");
                exit(1);
            }

            // Open client FIFO for writing
            open_read_fifo();

            // Wait for response from server
            char response[1024];
            memset(response, 0, sizeof(response));
            if (read(fd_read_client, response, sizeof(response)) == -1) {
                perror("Failed to read response from server");
                exit(1);
            }
            printf("Server response:\n%s", response);
            close(fd_read_client);
        }

        else if (strncmp(command, "download ", 9) == 0) {
            char request[512];
            snprintf(request, sizeof(request), "%d %s\n", getpid(),command);
            // Send the download command and filename to the server
            if (write(fd_write_client, request, strlen(request)) == -1) {
                perror("Failed to send download request to server");
                exit(1);
            }

            open_read_fifo();

            // Wait for response from server
            char response[1024];
            memset(response, 0, sizeof(response));
            if (read(fd_read_client, response, sizeof(response)) == -1) {
                perror("Failed to read response from server");
                exit(1);
            }
            printf("Server response:\n%s", response);

            close(fd_read_client);
        }

        else if (strcmp(command, "quit") == 0) {
            // Send request to server to write to log file
            char newcommand[100];
            sprintf(newcommand, "%d quit\n", getpid());

            if (write(fd_write_client, newcommand, strlen(newcommand)) == -1) {
                perror("Failed to send write request to server");
                exit(1);
            }
            printf("quit request sent to server.\n");

            // Open client FIFO for writing
            open_read_fifo();

            // Wait for response from server
            char log_message[256];
            if (read(fd_read_client, log_message, sizeof(log_message)) == -1) {
                perror("Failed to read log message from server");
                exit(1);
            }
            strtok(log_message, "\n");
            printf("Log message from server: %s\n", log_message);
            // Close named pipe and exit
            close(fd_read_client);
            exit(0);

        } 

        else if (strcmp(command, "killServer") == 0) {
            // Send kill request to server and terminate client program

            char newcommand[100];
            sprintf(newcommand, "%d killServer\n", getpid());

            if (write(fd_write_client,newcommand, strlen(newcommand)) == -1) {
                perror("Failed to send kill request to server");
                exit(1);
            }
            printf("Kill request sent to server.\n");
        }
        
         else {
            printf("Invalid command. Type 'help' for a list of available commands.\n");
        }
    }
    return 0;
}