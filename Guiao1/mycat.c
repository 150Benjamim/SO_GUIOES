#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>

void mycat(){

    int buffer_size = 20;
    char buffer[buffer_size];
    size_t read_bytes;

    while ( (read_bytes = read(STDIN_FILENO,buffer,buffer_size)) > 0){
        write(STDOUT_FILENO,buffer,read_bytes);
    }
}


int main() {
    mycat();

    return 0;
}
