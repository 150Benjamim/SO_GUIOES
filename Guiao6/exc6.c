#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>
#include <sys/wait.h>

#include <stdio.h>


int main(){

    int number_processes = 4;
    int fd[number_processes-1][2];

    if (pipe(fd[0])<0){
        perror("erro a criar pipe anónimo");
        return -1;
    }


    if (fork()==0){

        close(fd[0][0]);

        if (dup2(fd[0][1],STDOUT_FILENO)<0){
            perror("[filho] erro dup2");
            _exit(-1);
        }

        close(fd[0][1]);

        execlp("grep","grep", "-v", "^#", "/etc/passwd", NULL);

        _exit(0);
    }

    close(fd[0][1]);

    if (pipe(fd[1])<0){
        perror("erro a criar pipe anónimo");
        return -1;
    }

    if (fork()==0){

        if (dup2(fd[0][0],STDIN_FILENO)<0){
            perror("[filho] erro dup2");
            _exit(-1);
        }

        close(fd[0][0]);
        close(fd[1][0]);

        if (dup2(fd[1][1],STDOUT_FILENO)<0){
            perror("[filho] erro dup2");
            _exit(-1);
        }

        close(fd[1][1]);

        execlp("cut","cut", "-f7", "-d:", NULL);

        _exit(0);
    }

    close(fd[0][0]);

    close(fd[1][1]);

    if (pipe(fd[2])<0){
        perror("erro a criar pipe anónimo");
        return -1;
    }

    if (fork()==0){

        if (dup2(fd[1][0],STDIN_FILENO)<0){
            perror("[filho] erro dup2");
            _exit(-1);
        }

        close(fd[1][0]);

        if (dup2(fd[2][1],STDOUT_FILENO)<0){
            perror("[filho] erro dup2");
            _exit(-1);
        }

        close(fd[2][1]);

        execlp("uniq", "uniq", NULL);

        _exit(0);
    }


   close (fd[2][1]);


    if (fork()==0){

        if (dup2(fd[2][0],STDIN_FILENO)<0){
            perror("[filho] erro dup2");
            _exit(-1);
        }

        close(fd[2][0]);


        execlp("wc", "wc", "-l", NULL);

        _exit(0);
    }

    
    close(fd[2][0]);

    while (wait(NULL)>0);

    return 0;
}