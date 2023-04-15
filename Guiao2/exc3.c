#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */

#include <stdio.h>


int main() {

    int status;

    for (int i = 0; i<10; i++){
        if (fork() == 0){
            printf("[Filho] Pid: %d\n", getpid());
            printf("[Filho] Pid do pai: %d\n", getppid());
            _exit(i+1);
        }
        else {
            wait(&status);
            printf("[Pai] Código de saída do filho: %d\n", WEXITSTATUS(status));
        }
    }


}