#include<fcntl.h> // for fcntl()
#include<errno.h> // for errno
#include<unistd.h> // for open()
#include<stdio.h> // for perror


int my_dup(int oldfd){
    // create file descriptor
    int newfd = fcntl(oldfd,F_DUPFD,0);

    if(newfd == -1) // if new fd cannot open 
        perror("my_dup");

    return newfd;
}


int my_dup2(int oldfd, int newfd){
    //special case where oldfd equals newfd
    if(oldfd == newfd){
        //check if oldfd is not valid
        if(fcntl(oldfd,F_GETFD) == -1){
            errno = EBADF;
            return -1;
        }
        return newfd;
    }
    // close newfd if it is already open
    close(newfd);

    // create a duplicate filedescriptor with F_DUPFD
    int result = fcntl(oldfd,F_DUPFD,newfd);

    if(result == -1)
        perror("my_dup2");
    
    return result;
}

int main(){
    int fd1,fd2,fd3;
    char buffer[] = "Mahir Kayadelen CSE344";
    char buffer1[10];

    fd1 = open("test.txt",O_RDWR |O_CREAT,0644);
    if(fd1 == -1){
        perror("open");
        return 1;
    }
    
    write(fd1,buffer,23); // write buffer to the file using fd1
    printf("created file descriptor1 (fd1) and wrote 'Mahir Kayadelen CSE344' via write()\n");
    lseek(fd1,0,SEEK_SET); // seek to beginning file

    read(fd1,buffer1,5);
    buffer1[5] =  '\0';
    printf("fd1 read 5byte:%s\n",buffer1);
    

    
    //duplicate fd1 using my_dup()
    fd2 = my_dup(fd1);
    if(fd2 == -1){
        perror("my_dup");
        return 1;
    }
    // read the next 10 characters of the file using fd2
    read(fd2,buffer1,10);
    buffer1[10] = '\0';
    printf("duplicate fd1 using my_dup() and read fd2 10 bytes:%s\n",buffer1);

    // duplicate fd2 using my_dup2()
    fd3 = my_dup2(fd2,5);
    if(fd3 == -1){
        perror("my_dup2");
        return 1;
    }
    // read the next 7 characters of the file using fd3
    read(fd3,buffer1,7);
    buffer1[7] = '\0';
    printf("duplicate fd2 using my_dup2() and read the next 7 characters of the file using fd3:%s\n",buffer1);

    // write to fd1 and read from fd2 to verify file offset sharing
    printf("write to fd1 and read from fd2 to verify file offset sharing\n");
    lseek(fd1,0,SEEK_SET);
    write(fd1,"12345",5);
    printf("write 12345 with fd1\n");
    lseek(fd1,0,SEEK_SET);
    read(fd2,buffer,5);
    buffer[5] = '\0';
    printf("fd2 read after write:%s\n",buffer);

    close(fd1);
    close(fd2);
    close(fd3);
    return 0;
}