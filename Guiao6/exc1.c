#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>
#include <sys/wait.h>

#include <stdio.h>


int main() {

    int fd_passwd, fd_saida, fd_erros;

    int saved_stdout = dup(STDOUT_FILENO);

    if ((fd_passwd = open("/etc/passwd", O_RDONLY, 0660))<0){
        perror("erro a abrir passwd");
        return -1;
    }

    if ((fd_saida = open("saida.txt", O_WRONLY | O_CREAT | O_TRUNC, 0660))<0){
        perror("erro a abrir saida.txt");
        return -1;
    }

    if ((fd_erros = open("erros.txt", O_WRONLY | O_CREAT | O_TRUNC, 0660))<0){
        perror("erro a abrir erros.txt");
        return -1;
    }


    if (dup2(fd_passwd, STDIN_FILENO)<0){
        perror("erro a copiar fd stdin para passwd");
        return -1;
    }

    close(fd_passwd);

    if (dup2(fd_saida, STDOUT_FILENO)<0){
        perror("erro a copiar fd stdout para saida.txt");
        return -1;
    }

    close(fd_saida);

    if (dup2(fd_erros, STDERR_FILENO)<0){
        perror("erro a copiar fd stderr para erros.txt");
        return -1;
    }

    close(fd_erros);


    int status;

    setbuf(stdout,NULL);

    for (int i = 0; i<5; i++){
        if (fork() == 0){
            printf("[Filho] teste teste printf\n");
            _exit(0);
        }
    }

    while (wait(&status)>0){
        if (!WIFEXITED(status)) return -1;
    }



    if (fork()==0){
        if (execlp("wc","wc",NULL)<0){
            printf("erro a executar wc");
            _exit(-1);
        }
        _exit(0);
    }

    if (wait(&status) < 0){
        perror("erro waiting child");
        return -1;
    }

    if (!WIFEXITED(status)) return -1;
    else{
        if (WEXITSTATUS(status) == -1) return -1;
    }


    printf("terminei\n");



    dup2(saved_stdout,STDOUT_FILENO);

    close(saved_stdout);


    printf("terminei\n");


    return 0;
}
