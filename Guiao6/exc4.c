#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>
#include <sys/wait.h>

#include <stdio.h>


int main(){


    int fd[2];

    if (pipe(fd)<0){
        perror("erro a criar pipe anónimo");
        return -1;
    }


    if (fork()==0){

        close(fd[1]);

        if (dup2(fd[0],STDIN_FILENO)<0){
            perror("[filho] erro dup2");
            _exit(-1);
        }

        execlp("wc","wc",NULL);

        close(fd[0]);

        _exit(0);
    }


    close(fd[0]);

    int size = 128;
    size_t read_size;
    char buffer[size];
    while ((read_size = read(STDIN_FILENO,buffer,size))>0){
        write(fd[1],buffer,read_size);
    }

    close(fd[1]);

    wait(NULL);

    return 0;
}