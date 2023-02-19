#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>


ssize_t readln(int fd, char* line, size_t size){

    ssize_t i = 0;

    for (; read(fd, &line[i], 1) > 0 && i < size; i++) {
        if (line[i] == '\n')
            return i;
    }

    return i;
}


int main(){

    size_t size_bytes = 20;
    int i = 1;
    while (1){
        char line[size_bytes];
        if (readln(STDIN_FILENO,line,size_bytes) != 0){
            printf("     %d  %s", i, line);
            i++;
        }
    }

    return 0;
}