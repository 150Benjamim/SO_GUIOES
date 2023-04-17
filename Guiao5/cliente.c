#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>

#include <stdio.h>

int main() {

    int fd;

    if ((fd = open("fifoServerClient",O_WRONLY,0660))==-1){
        perror("Erro a abrir FIFO");
        return -1;
    }

    int buffer_size = 50;
    char buffer[buffer_size];
    int read_bytes;

    while ((read_bytes = read(STDIN_FILENO,buffer,buffer_size))>0){
        write(fd,buffer,read_bytes);
    }

    close(fd);

    return 0;
}
