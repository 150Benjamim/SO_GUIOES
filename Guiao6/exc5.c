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

        close(fd[0]);

        if (dup2(fd[1],STDOUT_FILENO)<0){
            perror("[filho] erro dup2");
            _exit(-1);
        }

        close(fd[1]);

        execlp("ls","ls", "/etc", NULL);

        _exit(0);
    }

    close(fd[1]);

    if (fork()==0){

        if (dup2(fd[0],STDIN_FILENO)<0){
            perror("[filho] erro dup2");
            _exit(-1);
        }

        close(fd[0]);

        execlp("wc","wc", "-l", NULL);

        _exit(0);
    }

    close(fd[0]);

    while (wait(NULL)>0);

    return 0;
}