#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h>

#include <stdio.h>

int main() {

    int pd[2];
    int buffer;

    if (pipe(pd)<0) {
        perror("Pipe não foi criado");
        return -1;
    }

    switch (fork()) {
        case -1:
            perror("Fork não foi efetuado");
            return -1;

        case 0:
            close(pd[1]);

            read(pd[0],&buffer,sizeof (int));
            printf("[Filho] Li do pipe o inteiro: %d\n", buffer);

            close(pd[0]);

            _exit(0);

        default:
            close(pd[0]);

            int toWrite = 10;

            //sleep(5);

            write(pd[1],&toWrite,sizeof (int));
            printf("[Pai] Escrevi no pipe o inteiro: %d\n", toWrite);

            close(pd[1]);

            wait(NULL);
    }


    return 0;
}
