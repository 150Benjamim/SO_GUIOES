#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define linhas 5
#define colunas 1000


int findNumber(int matriz[linhas][colunas], int key){

    pid_t waiter[linhas];
    pid_t pid;
    int status;
    int r = 0;

    for (int l = 0; l<linhas; l++){

        if ((pid = fork()) == 0){
            for (int c = 0; c<colunas; c++)
                if (matriz[l][c] == key) _exit(l+1);
            _exit(0);
        }

        else
            waiter[l] = pid;
    }

    for (int i = 0; i<linhas; i++){
        waitpid(waiter[i],&status,0);
        if (WIFEXITED(status))
            if (WEXITSTATUS(status)>0) {
            printf("Número encontrado na linha: %d\n", WEXITSTATUS(status));
            r = 1;
        }
    }

    return r;
}




int main(int argc, char** argv) {

    if (argc<2) return 0;

    srand(time(NULL));

    int matriz[linhas][colunas];

    for (int l = 0; l<linhas; l++)
        for (int c = 0; c<colunas; c++)
            matriz[l][c] = rand() % 5000;

    int key = atoi(argv[1]);

    if (findNumber(matriz,key))
        printf("Existe o número %d na matriz!\n", key);
    else
        printf("Não existe o número %d na matriz!\n", key);

}