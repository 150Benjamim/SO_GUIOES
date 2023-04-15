#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h>


int main(int argc, char** argv) {

    for (int i = 1; i<argc; i++)
    {
        if (fork()==0){
            execlp(argv[i],argv[i], (char*) NULL);
            _exit(i);
        }
    }

    while (wait(NULL)>0);


    return 0;
}
