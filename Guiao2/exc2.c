#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */

#include <stdio.h>



int main() {

    pid_t pid;

    if ((pid = fork()) == 0){
        printf("[Filho] Pid: %d\n",getpid());
        printf("[Filho] Pid do Pai: %d\n",getppid());
        _exit(0);
    }
    else{
        printf("[Pai] Pid: %d\n",getpid());
        printf("[Pai] Pid do Pai: %d\n",getppid());
        printf("[Pai] Pid do Filho: %d\n", pid);
    }

    return 0;
}