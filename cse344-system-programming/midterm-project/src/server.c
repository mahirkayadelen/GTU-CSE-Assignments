#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <semaphore.h>
#include <sys/wait.h> // for waitpid
#include <dirent.h> // for perform directory command "list"
#include <sys/file.h> // file locking for avoid issues

int fd_read; // server main fifo for receive connection requests
int fd_write; // server main fifo for send connection status
int log_fd;
int general_log_fd;
int *client_fds;
int* client_ids;
sem_t *semaphore; // Semaphore for limiting the number of clients
pid_t *child_pids; // array to store child PIDs
int child_count; // count of current child processes
int client_count = 0;
char log_buffer[256];
pid_t parent_pid;
char *dirname;


void handle_signal(int sig) {
    if(sig == SIGUSR1 || sig == SIGINT ){
        if(sig == SIGINT){
        if (getpid() == parent_pid) {
        printf(">>Received signal %d, terminating...\n>>bye\n", sig);
        sprintf(log_buffer, ">>Received signal %d, terminating...\n>>bye\n", sig);
        write(general_log_fd, log_buffer, strlen(log_buffer));
        }
        }

        // Send kill signal to child processes
        for (int i = 0; i < child_count; i++) {
            kill(child_pids[i], SIGUSR2);
        }
        // send kill signal to clients
        for (int i = 0; i < client_count; i++) {
            // write(client_fds[i], "Server is shutting down.\n", 25);
            kill(client_ids[i], SIGUSR2);
            kill(client_ids[i], SIGKILL);
        }


        // Close and remove client FIFOs
        for (int i = 0; i < child_count; i++) {
            char client_fifo_write[100];
            char client_fifo_read[100];
            sprintf(client_fifo_write, "/tmp/my_named_pipe_write_%d", child_pids[i]);
            sprintf(client_fifo_read, "/tmp/my_named_pipe_read_%d", child_pids[i]);
            close(open(client_fifo_write, O_WRONLY)); // Necessary to break read() in child
            close(open(client_fifo_read, O_RDONLY));  // Necessary to break read() in main
            unlink(client_fifo_write);
            unlink(client_fifo_read);
        }
        // remove main FIFO's
        unlink("/tmp/my_named_pipe_read");
        unlink("/tmp/my_named_pipe_write");

        // release semaphore
        sem_unlink("/my_named_semaphore");
        
        // Close and remove main FIFO
        close(fd_write);
        close(fd_read);

        // Close log file
        if (close(log_fd) == -1) {
            perror("Failed to close log file");
            exit(1);
        }
        if (close(general_log_fd) == -1) {
            perror("Failed to close log file");
            exit(1);
        }


        // Clean up resources
        free(client_ids);
        free(client_fds);
        free(child_pids);

        exit(0);
    }
}


void handle_sigchld(int sig) { // handling when any child process in server terminates
    pid_t pid;
    int status;

    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) { // if any of child exit() semaphore will increment
        // Remove pid from child_pids array
        for (int i = 0; i < child_count; i++) { // finds PID and delete it
            if (child_pids[i] == pid) {
                // Shift remaining elements down
                for (int j = i; j < child_count - 1; j++) {
                    child_pids[j] = child_pids[j + 1];
                }
                child_count--;
                break;
            }
        }
    }
    sem_post(semaphore);
}


void handle_client_command(int fd_write, char *command,int clientnum) {

    char *filename;
    char response[512];
    memset(response, 0, sizeof(response));
    if (strncmp(command, "Connect ", 8) == 0) {
        sprintf(response, "Status 1\n");
    }
    else if (strcmp(command, "help") == 0) {
        sprintf(response, "Available commands: help, list, quit, killServer\n");
    } 
    else if (strcmp(command, "list") == 0) {
        DIR *dir;
        struct dirent *entry;
        struct stat statbuf;
        dir = opendir(dirname);  // Open the current directory
        if (dir == NULL) {
            sprintf(response, "Failed to open directory.\n");
        } else {
            strcpy(response, "");  // Clear the response
            char file_path[261]; // Tam yol bilgisini saklamak için bir karakter dizisi
            while ((entry = readdir(dir)) != NULL) {
                sprintf(file_path, "%s/%s", dirname,entry->d_name); // Tam yol bilgisini oluştur
                stat(file_path, &statbuf);
                if (S_ISREG(statbuf.st_mode)) {  // If the entry is a regular file...
                    strcat(response, entry->d_name);
                    strcat(response, "\n");
                }
            }
            closedir(dir);
        }
        write(fd_write, response, strlen(response));
    }
    else if (strncmp(command, "readF ", 6) == 0) {

        char file_buffer[1024];

        int line_number = -1;
        filename = strtok(command + 6, " ");
        char *line_str = strtok(NULL, " ");
        if (line_str != NULL) {
            line_number = atoi(line_str) -1; // for take 1st line as 1
        }
            char path[512];
            sprintf(path, "%s/%s", dirname,filename);


        FILE *file = fopen(path, "r");
        if (file == NULL) {
            sprintf(response, "Failed to open file: %s\n", filename);
            write(fd_write, response, strlen(response));
        } else {
            if(flock(fileno(file), LOCK_EX | LOCK_NB) != 0){
                sprintf(response, "File is locked by another client.\n");
                write(fd_write, response, strlen(response));
            }
            else{
                if (line_number == -1) {
                    // If no line number is given, send the whole file
                    long content_size = 0;
                    fseek(file, 0, SEEK_END);
                    content_size = ftell(file);
                    rewind(file);
                    write(fd_write, &content_size, sizeof(content_size));
                    while (fgets(file_buffer, sizeof(file_buffer), file) != NULL) {
                        write(fd_write, file_buffer, strlen(file_buffer));
                    }
                } else {
                    // If a line number is given, send only that line
                    int current_line = 0;
                    while (fgets(file_buffer, sizeof(file_buffer), file) != NULL) {
                        if (current_line == line_number) {
                            long content_size = strlen(file_buffer);
                            write(fd_write, &content_size, sizeof(content_size));
                            write(fd_write, file_buffer, content_size);
                            break;
                        }
                        current_line++;
                    }
                }
                flock(fileno(file), LOCK_UN);
            }
            fclose(file);
            return;
        }
    }

    else if (strncmp(command, "writeT ", 7) == 0) {
        filename = strtok(command + 7, " ");
        char *line_str = strtok(NULL, " ");
        char *content = strtok(NULL, "");
        if (content == NULL) {
            content = line_str;
            line_str = NULL;
        }
        int line_number = line_str != NULL ? atoi(line_str) : -1;

        char path[512];
        sprintf(path, "%s/%s", dirname,filename);

        FILE *file = fopen(path, "a+");
        if (file == NULL) {
            sprintf(response, "Failed to open or create file: %s\n", filename);
            write(fd_write, response, strlen(response));
        } else {
            if (flock(fileno(file), LOCK_EX | LOCK_NB) != 0) {
                sprintf(response, "File is locked by another client.\n");
                write(fd_write, response, strlen(response));
            } else {
                if (line_number == -1) {
                    // If no line number is given, write to the end of file
                    fputs(content, file);
                    fputs("\n", file);
                } else {
                    char temp_filename[FILENAME_MAX];
                    sprintf(temp_filename, "%s.tmp", filename);
                    FILE *temp_file = fopen(temp_filename, "w");

                    char file_buffer[1024];
                    int current_line = 1;
                    while (fgets(file_buffer, sizeof(file_buffer), file) != NULL) {
                        if (current_line == line_number) {
                            fputs(content, temp_file);
                            fputs("\n", temp_file);
                        } else {
                            fputs(file_buffer, temp_file);
                        }
                        current_line++;
                    }
                    if (current_line <= line_number) {
                        fputs(content, temp_file);
                        fputs("\n", temp_file);
                    }
                    fclose(temp_file);
                    rename(temp_filename, path);
                }
                sprintf(response, "Write successful.\n");
                write(fd_write, response, strlen(response));
                flock(fileno(file), LOCK_UN);
            }
            fclose(file);
            return;
        }
    }

    else if (strncmp(command, "upload ", 7) == 0) {
        // Extract the filename from the command
        filename = strtok(command + 7, " ");
        // Check if the file exists in the client's current directory
        struct stat statbuf;
        if (stat(filename, &statbuf) == -1) {
            sprintf(response, "File does not exist.\n");
        } else if (S_ISDIR(statbuf.st_mode)) {
            sprintf(response, "The name refers to a directory, not a file.\n");
        } else {
            // Check if the file exists in the server's directory
            char file_path[261];
            sprintf(file_path, "%s/%s", dirname, filename);
            if (access(file_path, F_OK) != -1) {
                sprintf(response, "File with the same name already exists in the server's directory.\n");
            } else {
                // Open the file for reading
                FILE *file = fopen(filename, "rb");
                if (file == NULL) {
                    sprintf(response, "Failed to open file.\n");
                } else {
                    // Open the destination file for writing
                    FILE *dest = fopen(file_path, "wb");
                    if (dest == NULL) {
                        sprintf(response, "Failed to create file in the server's directory.\n");
                    } else {
                        // Copy the file in chunks
                        char buffer[1024];
                        size_t total_bytes = 0;
                        size_t bytes;
                        while ((bytes = fread(buffer, 1, sizeof(buffer), file)) > 0) {

                            fwrite(buffer, 1, bytes, dest);
                            total_bytes += bytes;
                        }
                        fclose(file);
                        fclose(dest);
                        sprintf(response, "File uploaded successfully. Transferred %zu bytes.\n", total_bytes);
                    }
                }
            }
        }
        write(fd_write, response, strlen(response));
    }


    else if (strncmp(command, "download ", 9) == 0) {
        // Extract the filename from the command
        filename = strtok(command + 9, " ");
        // Check if the file exists in the server's directory
        char file_path[261];
        sprintf(file_path, "%s/%s", dirname, filename);
        struct stat statbuf;
        if (stat(file_path, &statbuf) == -1) {
            sprintf(response, "File does not exist in the server's directory.\n");
        } else if (S_ISDIR(statbuf.st_mode)) {
            sprintf(response, "The name refers to a directory, not a file.\n");
        } else {
            // Check if the file already exists in the client's directory
            if (access(filename, F_OK) != -1) {
                sprintf(response, "File with the same name already exists in the client's directory.\n");
            } else {
                // Copy the file to the client's directory
                FILE *source = fopen(file_path, "rb");
                if (source == NULL) {
                    sprintf(response, "Failed to open file in the server's directory.\n");
                } else {
                    FILE *dest = fopen(filename, "wb");
                    if (dest == NULL) {
                        sprintf(response, "Failed to create file in the client's directory.\n");
                    } else {
                        size_t total_bytes = 0;
                        char buffer[1024];
                        size_t bytes;
                        while ((bytes = fread(buffer, 1, sizeof(buffer), source)) > 0) {
                            fwrite(buffer, 1, bytes, dest);
                            total_bytes += bytes;
                        }
                        fclose(source);
                        fclose(dest);
                        sprintf(response, "File downloaded successfully. Transferred %zu bytes.\n", total_bytes);
                    }
                }
            }
        }
        write(fd_write, response, strlen(response));
    }

    
    else if (strcmp(command, "quit") == 0) {
        sprintf(response, "client is shutting down.\n");
        write(fd_write, response, strlen(response));

        sprintf(log_buffer, "client%d disconnected\n",client_count);
        write(general_log_fd, log_buffer, strlen(log_buffer));
        printf("client%d disconnected\n",client_count);
        exit(0); // exit child process
    }

    else if (strcmp(command, "killServer") == 0) {
        sprintf(response, "Terminating server.\n");
        write(fd_write, response, strlen(response));

        sprintf(log_buffer, ">>Kill signal from client%d.. Terminating...\n>>bye\n",clientnum);
        write(general_log_fd, log_buffer, strlen(log_buffer));
        printf(">>Kill signal from client%d.. Terminating...\n>>bye\n",clientnum);
        kill(getppid(), SIGUSR1);  // Send SIGUSR1 signal to parent process
    } 
    
    else {
        sprintf(response, "Unknown command: %s\n", command);
        write(fd_write, response, strlen(response));
    }

}

int main(int argc, char *argv[]) {

    int max_clients;
    parent_pid = getpid();
    struct sigaction sa;

    if (argc != 3) {
        printf("Usage: %s <dirname> <max. #ofClients>\n", argv[0]);
        exit(1);
    }

    dirname = argv[1];
    max_clients = atoi(argv[2]);

    // allocate memorys
    client_ids = (int*)malloc(max_clients * sizeof(int));
    client_fds = (int*)malloc(max_clients * sizeof(int));
    child_pids = (pid_t*)malloc(max_clients * sizeof(pid_t));

    // Create directory if it does not exist
    struct stat st;
    if (stat(dirname, &st) == -1) {
        mkdir(dirname, 0700);
    }

    // Create log file for clients
    char log_file[100];

    // Create log file for all commands
    char log_file_general[100];
    sprintf(log_file_general,"%s/all_logs.txt",dirname);
    general_log_fd = open(log_file_general, O_CREAT | O_WRONLY, 0600); // open general log file
    if (log_fd == -1) {
        perror("Failed to create general log file");
        exit(1);
    }

    sem_unlink("/my_named_semaphore"); // if semaphore already exists, delete it.
    semaphore = sem_open("/my_named_semaphore", O_CREAT | O_EXCL, 0644, max_clients);
    if (semaphore == SEM_FAILED) {
        perror("Failed to create semaphore");
        exit(1);
    }

    
    // Install signal handler for SIGUSR1 and SIGINT
    sa.sa_handler = handle_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("Failed to install signal handler for SIGUSR1");
        exit(1);
    }

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Failed to install signal handler for SIGINT");
        exit(1);
    }



    // Install signal handler for SIGCHLD
    sa.sa_handler = handle_sigchld;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART; // To automatically restart system calls
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    printf(">> Server Started PID %d\n", getpid());
    sprintf(log_buffer, ">> Server Started PID %d\n", getpid());
    write(general_log_fd, log_buffer, strlen(log_buffer));


    // Create named pipes for communication with clients

    if (mkfifo("/tmp/my_named_pipe_read", S_IRWXU) < 0) {
        if (errno == EEXIST) {
            unlink("/tmp/my_named_pipe_read");  // remove existing named pipe
            if (mkfifo("/tmp/my_named_pipe_read", S_IRWXU) < 0) {
                perror("mkfifo");
                exit(1);
            }
        } else {
            perror("mkfifo");
            exit(1);
        }
    }

    if (mkfifo("/tmp/my_named_pipe_write", S_IRWXU) < 0) {
        if (errno == EEXIST) {
            unlink("/tmp/my_named_pipe_write");  // remove existing named pipe
            if (mkfifo("/tmp/my_named_pipe_write", S_IRWXU) < 0) {
                perror("mkfifo");
                exit(1);
            }
        } else {
            perror("mkfifo");
            exit(1);
        }
    }

    // Open named pipe for reading
    fd_read = open("/tmp/my_named_pipe_read", O_RDWR);
    if (fd_read == -1) {
        perror("Failed to open named pipe for reading");
        exit(1);
    }

    // Open named pipe for writing
    fd_write = open("/tmp/my_named_pipe_write", O_RDWR);
    if (fd_write == -1) {
        perror("Failed to open named pipe for writing");
        exit(1);
    }

    printf(">> Waiting for clients...\n");
    sprintf(log_buffer, ">> Waiting for clients...\n");
    write(general_log_fd, log_buffer, strlen(log_buffer));




    // Loop to handle client commands
    while (1) {
        // Read client PID from main FIFO
        char buf[100];
        int num_bytes = read(fd_read, buf, sizeof(buf));

        int client_pid;
        char command[20];
        memset(command, 0, sizeof(command));
        
        sscanf(buf, "%d %s", &client_pid, command); // PID'yi ve komutu oku

        sprintf(log_file, "%s/log_%d.txt", dirname,client_pid); // create clients log file with clients PID
        log_fd = open(log_file, O_CREAT | O_WRONLY, 0600); // opens clients log file 
        if (log_fd == -1) {
            perror("Failed to create log file");
            exit(1);
        }

        
        if (client_pid == -1) {
            if (errno == EINTR) {
                // Interrupted by signal, try again
                continue;
            } else {
                // Error reading from pipe
                perror("Failed to read from named pipe");
                exit(1);
            }
        } else if (client_pid == 0) {
            printf("break out\n");
            // End of file, break out of loop
            break;
        }
        int flag = 0; // for the desired menu design, if the client log in after waits queue, to inform the server 
        if(child_count >=  max_clients){
            if(strcmp("tryConnect",command)  == 0){
            printf(">>Connection request PID %d… Que FULL. Client leaving... \n",client_pid);
            sprintf(log_buffer, ">>Connection request PID %d… Que FULL. Client leaving... \n",client_pid);
            write(general_log_fd, log_buffer, strlen(log_buffer));

                char response[256];
                sprintf(response, "Full");
                write(fd_write, response, strlen(response));
                continue;
            }
            else{
                sprintf(log_buffer, ">>Connection request PID %d… Que FULL. \n",client_pid);
                write(general_log_fd, log_buffer, strlen(log_buffer));
                printf(">>Connection request PID %d… Que FULL. \n",client_pid);
            }
            flag = 1;
        }
        else{
            sprintf(log_buffer, ">>Client PID:'%d' connected as 'client%d'\n", client_pid,client_count+1);
            write(general_log_fd, log_buffer, strlen(log_buffer));
            printf(">>Client PID:'%d' connected as 'client%d'\n", client_pid,client_count+1);
        }

        if (sem_wait(semaphore) == -1) {
            perror("Failed to wait on semaphore");
            exit(1);
        }
        if(flag){ // for desired menu design, after queue comes waiting client, server info.
            sprintf(log_buffer, ">>Client PID:'%d' connected as 'client%d'\n", client_pid,client_count+1);
            write(general_log_fd, log_buffer, strlen(log_buffer));
            printf(">>Client PID:'%d' connected as 'client%d'\n", client_pid,client_count+1);
        }
        
        
        client_ids[client_count++] = client_pid; // store client PID's for able to kill all after any killServer command

        // Create new  PID-NAMED FIFOs for communication with client
        char client_fifo_write[100];
        char client_fifo_read[100];
        sprintf(client_fifo_write, "/tmp/my_named_pipe_write_%d", client_pid);
        sprintf(client_fifo_read, "/tmp/my_named_pipe_read_%d", client_pid);

        mkfifo(client_fifo_write, 0666);
        mkfifo(client_fifo_read, 0666);

        // Open client FIFO for writing
        int fd_write_client = open(client_fifo_write, O_RDWR);
        if (fd_write_client == -1) {
            perror("Failed to open client FIFO for writing");
            exit(1);
        }

        // Open client FIFO for reading
        int fd_read_client = open(client_fifo_read, O_RDWR);
        if (fd_read_client == -1) {
            perror("Failed to open client FIFO for reading");
            exit(1);
        }


        // Create new child process to handle client
        pid_t pid = fork();
        if (pid == -1) {
            perror("Failed to fork child process");
            exit(1);
        } else if (pid == 0) {
            int client_numstatic = client_count;
            char response[256];
            sprintf(response, "Status 1");
            write(fd_write, response, strlen(response));
            // Child process: handle client commands and then terminate
            while(1) {
                int num_bytes = read(fd_read_client, buf, sizeof(buf));
                if (num_bytes <= 0) {
                    break;
                }
                // Remove newline character from end of string
                buf[num_bytes - 1] = '\0';
                

                // Write client command to clients log file
                char client_name[10];
                sprintf(client_name, "client%d", getpid());
                char log_entry[256];
                sprintf(log_entry, "%s\n",buf);
                if (write(log_fd, log_entry, strlen(log_entry)) == -1) {
                    perror("Failed to write to log file");
                    exit(1);
                }
                sprintf(log_entry, "%s: %s\n", client_name, buf);
                if (write(general_log_fd, log_entry, strlen(log_entry)) == -1) {
                    perror("Failed to write to log file");
                    exit(1);
                }


                handle_client_command(fd_write_client, buf,client_numstatic);
            }
            exit(0);
        } else {
            // Parent process: add child PID to array and continue to next iteration of loop
            if (child_count < max_clients) {
                client_fds[child_count] = fd_write_client;
                child_pids[child_count++] = pid;
            }
            continue;
        }
    }
    return 0;
}