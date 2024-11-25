#include<fcntl.h> // open()
#include<unistd.h> // lseek() write()
#include<stdio.h> 
#include<stdlib.h> // exit
int main(int argc,char* argv[]){
    long int int_byte;
    sscanf(argv[2],"%ld",&int_byte);

    int _lseek = (argc == 4 && argv[3][0] == 'x'); // for convert commant-line argument(string) to int

    int flags = O_WRONLY | O_CREAT;
    if (!_lseek) {
        flags |= O_APPEND;
    }

    int fd = open(argv[1], flags, 0644);
    if (fd == -1) {
        perror("Error opening the file");
        exit(-1);
    }

    char byte = 'm';
    for(int i = 0;i<int_byte ; i++){
        if(_lseek){
            lseek(fd, 0, SEEK_END);
        }
        write(fd,&byte,1);
    }

    if(close(fd) == -1){
        perror("close");
        exit(EXIT_FAILURE);
    }
    return 0;
}