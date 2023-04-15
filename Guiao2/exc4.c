#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */

#include <stdio.h>


int main() {

    pid_t pid_filho;
    int status;

    for (int i = 0; i<10; i++){
        if (fork() == 0){
            printf("[Filho] Pid: %d\n", getpid());
            printf("[Filho] Pid do pai: %d\n", getppid());
            _exit(i+1);
        }
    }

    while ((pid_filho = wait(&status)) > 0){
        if (WIFEXITED(status)) printf("[Pai] O pid %d tem valor de saída: %d\n", pid_filho, WEXITSTATUS(status));
        else printf("Erro\n");
    }


    return 0;
}