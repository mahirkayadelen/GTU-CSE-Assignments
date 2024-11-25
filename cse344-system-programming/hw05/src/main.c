#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/time.h>
#include <errno.h>
#include <limits.h>
#include <signal.h>

typedef struct {
    char src_path[256];
    char dest_path[256];
} CopyRequest;

typedef struct {
    pthread_mutex_t lock;
    pthread_cond_t empty;
    pthread_cond_t full;
    CopyRequest* buffer; // dynamic array
    int buffer_size; // dynamic buffer size
    int in;
    int out;
    int count;
    int done;
    int total_files;
    long int total_bytes;
    int file_count[5]; // 5 file types
    pthread_mutex_t total_bytes_lock; // mutex for protecting total_bytes
} ThreadPool;

typedef struct {
    char src_dir[256];
    char dest_dir[256];
    ThreadPool* thread_pool;
} ProducerArgs;

typedef enum {
    REGULAR,
    DIRECTORY,
    FIFO,
    SOCKET,
    OTHER
} FileType;


ThreadPool thread_pool; // Declare global for sighandler access

void sighandler(int signum) {
    printf("\nReceived SIGINT, terminating program.\n");

    pthread_mutex_destroy(&thread_pool.lock);
    pthread_cond_destroy(&thread_pool.empty);
    pthread_cond_destroy(&thread_pool.full);
    pthread_mutex_destroy(&thread_pool.total_bytes_lock); 

    free(thread_pool.buffer);

    exit(signum);
}

void copy_file(const char* src_file, const char* dest_file, ThreadPool* thread_pool) {
    int src_fd, dest_fd;
    char buffer[4096];
    ssize_t bytes_read, bytes_written;
    
    src_fd = open(src_file, O_RDONLY);
    if (src_fd == -1) {
        if (errno == EMFILE) {
            fprintf(stderr, "Error opening source file, too many open files\n");
        } else {
            perror("Error opening source file");
        }
        return;
    }
    
    dest_fd = open(dest_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (dest_fd == -1) {
        if (errno == EMFILE) {
            fprintf(stderr, "Error opening destination file, too many open files\n");
        } else {
            perror("Error opening destination file");
        }
        close(src_fd);
        return;
    }
    
    while ((bytes_read = read(src_fd, buffer, sizeof(buffer))) > 0) {
        if (bytes_read == -1) {
            perror("Error reading from source file");
            break;
        }
        
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written == -1) {
            perror("Error writing to destination file");
            break;
        }
        pthread_mutex_lock(&thread_pool->total_bytes_lock);
        thread_pool->total_bytes += bytes_written;
        pthread_mutex_unlock(&thread_pool->total_bytes_lock);
    }
    
    close(src_fd);
    close(dest_fd);
}


FileType get_file_type(const char* file_path) {
    struct stat st;
    if (stat(file_path, &st) == -1) {
        perror("Error getting file status");
        return OTHER;
    }
    
    if (S_ISREG(st.st_mode))
        return REGULAR;
    else if (S_ISDIR(st.st_mode))
        return DIRECTORY;
    else if (S_ISFIFO(st.st_mode))
        return FIFO;
    else if (S_ISSOCK(st.st_mode))
        return SOCKET;
    else
        return OTHER;
}

void* producer_thread(void* arg) {
    ProducerArgs* producer_args = (ProducerArgs*)arg;
    ThreadPool* thread_pool = producer_args->thread_pool;
    DIR* dir;
    struct dirent* entry;
    char src_file[512], dest_file[512];
    
    dir = opendir(producer_args->src_dir);
    if (dir == NULL) {
        perror("Error opening source directory");
        return NULL;
    }
    
    // Ensure destination directory exists
    struct stat st = {0};
    if (stat(producer_args->dest_dir, &st) == -1) {
        if (mkdir(producer_args->dest_dir, 0700) == -1) {
            perror("Error creating destination directory");
        }
    }
    
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        
        snprintf(src_file, sizeof(src_file), "%s/%s", producer_args->src_dir, entry->d_name);
        snprintf(dest_file, sizeof(dest_file), "%s/%s", producer_args->dest_dir, entry->d_name);
        
        FileType file_type = get_file_type(src_file);
        if (file_type == DIRECTORY) {
            struct stat st;
            if (stat(dest_file, &st) == -1) {
                // Create destination directory
                if (mkdir(dest_file, 0700) == -1) {
                    perror("Error creating destination directory");
                    continue;
                }
            }
            
            ProducerArgs sub_producer_args;
            strncpy(sub_producer_args.src_dir, src_file, sizeof(sub_producer_args.src_dir));
            strncpy(sub_producer_args.dest_dir, dest_file, sizeof(sub_producer_args.dest_dir));
            sub_producer_args.thread_pool = thread_pool;
            
            pthread_mutex_lock(&thread_pool->lock);
            while (thread_pool->count == thread_pool->buffer_size) {
                pthread_cond_wait(&thread_pool->empty, &thread_pool->lock);
            }
            
            // Do not copy the directory here. Only update the statistics.
            thread_pool->total_files++;
            thread_pool->file_count[file_type]++;
            
            pthread_mutex_unlock(&thread_pool->lock);
            
            producer_thread(&sub_producer_args); // Recursively call producer_thread for subdirectories

        }
        else if(file_type == FIFO){
            if (mkfifo(dest_file, 0666) == -1) {
            perror("Error creating FIFO");

            thread_pool->total_files++;
            thread_pool->file_count[file_type]++;
            }
        }
        else {
            pthread_mutex_lock(&thread_pool->lock);
            while (thread_pool->count == thread_pool->buffer_size) {
                pthread_cond_wait(&thread_pool->empty, &thread_pool->lock);
            }
            
            strcpy(thread_pool->buffer[thread_pool->in].src_path, src_file);
            strcpy(thread_pool->buffer[thread_pool->in].dest_path, dest_file);
            
            thread_pool->in = (thread_pool->in + 1) % thread_pool->buffer_size;
            thread_pool->count++;
            
            // Update statistics
            thread_pool->total_files++;
            thread_pool->file_count[file_type]++;
            
            pthread_cond_signal(&thread_pool->full);
            pthread_mutex_unlock(&thread_pool->lock);
        }
    }
    
    closedir(dir);
    
    pthread_mutex_lock(&thread_pool->lock);
    thread_pool->done = 1;
    pthread_cond_broadcast(&thread_pool->full);
    pthread_mutex_unlock(&thread_pool->lock);
    
    return NULL;
}


void* consumer_thread(void* arg) {
    ThreadPool* thread_pool = (ThreadPool*)arg;
    
    while (1) {
        pthread_mutex_lock(&thread_pool->lock);
        while (thread_pool->count == 0 && !thread_pool->done) {
            pthread_cond_wait(&thread_pool->full, &thread_pool->lock);
        }
        
        if (thread_pool->count == 0 && thread_pool->done) {
            pthread_mutex_unlock(&thread_pool->lock);
            break;
        }
        
        CopyRequest request = thread_pool->buffer[thread_pool->out];
        thread_pool->out = (thread_pool->out + 1) % thread_pool->buffer_size;
        thread_pool->count--;
        
        pthread_cond_signal(&thread_pool->empty);
        pthread_mutex_unlock(&thread_pool->lock);
        
        copy_file(request.src_path, request.dest_path, thread_pool);
        
        printf("Copied file: %s\n", request.src_path);
    }
    
    return NULL;
}


int main(int argc, char* argv[]) {
    if (argc != 5) {
        printf("Usage: %s <buffer_size> <num_consumers> <src_dir> <dest_dir>\n", argv[0]);
        return 1;
    }
    
    int buffer_size = atoi(argv[1]);
    int num_consumers = atoi(argv[2]);
    
    if (buffer_size <= 0 || num_consumers <= 0) {
        printf("Invalid buffer size or number of consumers\n");
        return 1;
    }
    
    ThreadPool thread_pool;
    thread_pool.in = 0;
    thread_pool.out = 0;
    thread_pool.count = 0;
    thread_pool.done = 0;
    thread_pool.total_files = 0;
    thread_pool.total_bytes = 0;
    memset(thread_pool.file_count, 0, sizeof(thread_pool.file_count));
    thread_pool.buffer = (CopyRequest*) malloc(sizeof(CopyRequest) * buffer_size); // dynamic buffer
    thread_pool.buffer_size = buffer_size;


    struct sigaction action;

    action.sa_handler = sighandler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;

    if (sigaction(SIGINT, &action, NULL) < 0) {
        perror("sigaction");
        return 1;
    }



    pthread_mutex_init(&thread_pool.lock, NULL);
    pthread_cond_init(&thread_pool.empty, NULL);
    pthread_cond_init(&thread_pool.full, NULL);
    pthread_mutex_init(&thread_pool.total_bytes_lock, NULL); // mutex for protecting total_bytes

    ProducerArgs producer_args;
    strncpy(producer_args.src_dir, argv[3], sizeof(producer_args.src_dir));
    strncpy(producer_args.dest_dir, argv[4], sizeof(producer_args.dest_dir));
    producer_args.thread_pool = &thread_pool;

    pthread_t producer_tid;
    pthread_t consumer_tids[num_consumers];

    if (pthread_create(&producer_tid, NULL, producer_thread, &producer_args) != 0) {
        perror("Failed to create producer thread");
        return 1;
    }

    for (int i = 0; i < num_consumers; i++) {
        if (pthread_create(&consumer_tids[i], NULL, consumer_thread, &thread_pool) != 0) {
            perror("Failed to create consumer thread");
            return 1;
        }
    }
    
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);
    
    if (pthread_join(producer_tid, NULL) != 0) {
        perror("Failed to join producer thread");
        return 1;
    }

    for (int i = 0; i < num_consumers; i++) {
        if (pthread_join(consumer_tids[i], NULL) != 0) {
            perror("Failed to join consumer thread");
            return 1;
        }
    }
    
    gettimeofday(&end_time, NULL);

    pthread_mutex_destroy(&thread_pool.lock);
    pthread_cond_destroy(&thread_pool.empty);
    pthread_cond_destroy(&thread_pool.full);
    pthread_mutex_destroy(&thread_pool.total_bytes_lock); // destroying total_bytes_lock

    free(thread_pool.buffer); // deallocating the thread pool buffer

    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
    
    printf("Elapsed time: %.3f seconds\n", elapsed_time);
    printf("Total files copied: %d\n", thread_pool.total_files);
    printf("Total bytes copied: %ld\n", thread_pool.total_bytes);
    
    printf("File type statistics:\n");
    printf("Regular files: %d\n", thread_pool.file_count[REGULAR]);
    printf("Directories: %d\n", thread_pool.file_count[DIRECTORY]);
    printf("FIFO files: %d\n", thread_pool.file_count[FIFO]);
    printf("Socket files: %d\n", thread_pool.file_count[SOCKET]);
    printf("Other files: %d\n", thread_pool.file_count[OTHER]);
    
    return 0;
}