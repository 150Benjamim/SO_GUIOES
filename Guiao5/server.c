#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>
#include <sys/stat.h>


#include <stdio.h>

#define FIFO "fifoServerClient"

int main() {

    int fd_fifo, fd_log;
    struct stat stats;

    if (stat(FIFO,&stats) == 0)
        if (unlink(FIFO) < 0){
            perror("Unlinked failed");
            return -1;
        }

    if (mkfifo(FIFO,0660)==-1) {
        perror("Erro a criar FIFO");
        return -1;
    }


    if ((fd_fifo = open(FIFO,O_RDONLY,0660))==-1){
        perror("Erro a abrir FIFO");
        return -1;
    }

    if ((fd_log = open("log.txt",O_WRONLY | O_CREAT | O_TRUNC ,0660))==-1){
        perror("Erro a abrir logs");
        return -1;
    }


    int buffer_size = 50;
    char buffer[buffer_size];
    int read_bytes;

    while ((read_bytes = read(fd_fifo,buffer,buffer_size))>=0){
        write(fd_log,buffer,read_bytes);
    }

    close(fd_fifo);
    close(fd_log);

    return 0;
}
