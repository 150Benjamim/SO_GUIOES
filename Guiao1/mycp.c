#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>

int mycp(char *source_file, char *target_file){

    int source_fd = open(source_file,O_RDONLY);
    if (source_fd < 0) {
        perror("Erro a abrir source file");
        return 1;
    }

    int target_fd = open(target_file, O_CREAT | O_TRUNC | O_WRONLY , 0660);
    if (target_fd < 0) {
        perror("Erro a abrir target file");
        return 1;
    }

    int buffer_size = 50;
    char buffer[buffer_size];
    size_t read_bytes;

    while ( (read_bytes = read(source_fd,buffer,buffer_size)) > 0){
        write(target_fd,buffer,read_bytes);
    }

    close(source_fd);
    close(target_fd);

    return 0;
}


int main(int argc, char* argv[]) {

    return mycp(argv[1],argv[2]);
}
