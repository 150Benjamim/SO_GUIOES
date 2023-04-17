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
            close(pd[0]);

            for (int i = 0; i<5;i++) {
                write(pd[1], &i, sizeof(int));
                printf("[Filho] Escrevi no pipe o inteiro: %d\n", i);
            }

            close(pd[1]);

            _exit(0);

        default:
            close(pd[1]);

            while (read(pd[0],&buffer,sizeof (int))>0) {
                sleep(3);
                printf("[Pai] Li do pipe o inteiro: %d\n", buffer);
            }

            close(pd[0]);

            wait(NULL);
    }


    return 0;
}
