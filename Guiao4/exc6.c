#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define linhas 5
#define colunas 100


typedef struct vetor{
    int linha;
    int coluna;
    struct vetor* next;
}Vetor;


void randomMatriz(int matriz[linhas][colunas]) {

    srand(time(NULL));

    for (int l = 0; l<linhas; l++)
        for (int c = 0; c<colunas; c++)
            matriz[l][c] = rand() % 100;
}

int findNumber(int matriz[linhas][colunas], int key, Vetor *resultados){

    int fd[2];

    if (pipe(fd)<0) {
        perror("Pipe não foi criado");
        return -1;
    }

    for (int l = 0; l<linhas; l++){

        if (fork() == 0){
            close(fd[0]);
            Vetor *v = malloc(sizeof (Vetor));
            for (int c = 0; c<colunas; c++)
                if (matriz[l][c] == key) {
                    v->linha = l + 1;
                    v->coluna = c + 1;
                    v->next = NULL;
                    write(fd[1], v, sizeof(Vetor));
                }

            close(fd[1]);

            _exit(0);
        }

    }


    close(fd[1]);

    Vetor *aux;
    while (read(fd[0],resultados,sizeof (Vetor)) > 0){
        aux = resultados;
        resultados->next = malloc(sizeof (Vetor));
        resultados = resultados->next;
    }

    aux->next = NULL;
    free(resultados);

    close(fd[0]);

    wait(NULL);


    return 0;
}




int main(int argc, char** argv) {

    if (argc<2) return 0;

    int matriz[linhas][colunas];

    randomMatriz(matriz);

    Vetor *resultados = malloc(sizeof (Vetor));

    int key = atoi(argv[1]);


    findNumber(matriz,key,resultados);


    while (resultados!=NULL){
        printf("Resultado %d encontrado na linha %d e coluna %d\n", key,resultados->linha,resultados->coluna);
        resultados = resultados->next;
    }


}