#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h>


int main() {

    if (fork()==0){
        execlp("ls","ls","-l", (char*) NULL);
        _exit(0);
    }
    else
        wait(NULL);

    return 0;
}
