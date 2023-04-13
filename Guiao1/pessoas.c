#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct pessoa{
    char nome[30];
    int idade;
}Pessoa;


int addPessoa(char* pessoa[]) {

    int pessoas_file = open("pessoas.bin", O_RDWR | O_CREAT, 0660);
    if (pessoas_file < 0) {
        perror("Erro a abrir file");
        return 1;
    }

    int registo = 1;

    Pessoa p;

    while (read(pessoas_file, &p, sizeof(Pessoa)) > 0) {
        registo++;
        if (strcmp(p.nome, pessoa[0]) == 0) {
            printf("Pessoa já existe!\n");
            close(pessoas_file);
            return 0;
        }
    }

    Pessoa nova;
    strcpy(nova.nome, pessoa[0]);
    nova.idade = atoi(pessoa[1]);

    write(pessoas_file, &nova, sizeof(Pessoa));

    printf("registo %d\n", registo);

    close(pessoas_file);

    return 0;
}



int updateIdadeNome(char** pessoa){

    int pessoas_file = open("pessoas.bin", O_RDWR, 0660);
    if (pessoas_file < 0) {
        perror("Erro a abrir file");
        return 1;
    }

    Pessoa p;

    while (read(pessoas_file, &p, sizeof(Pessoa)) > 0) {
        if (strcmp(p.nome, pessoa[0]) == 0) {
            p.idade = atoi(pessoa[1]);
            lseek(pessoas_file,-sizeof (Pessoa), SEEK_CUR);
            write(pessoas_file,&p,sizeof (Pessoa));
            close(pessoas_file);
            return 0;
        }
    }

    printf("Pessoa não existe!\n");

    close(pessoas_file);

    return 0;
}



int updateIdadeRegisto(char** pessoa){

    int pessoas_file = open("pessoas.bin", O_RDWR, 0660);
    if (pessoas_file < 0) {
        perror("Erro a abrir file");
        return 1;
    }

    Pessoa p;

    int registo = atoi(pessoa[0]);

    lseek(pessoas_file,(registo-1)*sizeof (Pessoa),SEEK_SET);

    if (read(pessoas_file, &p, sizeof(Pessoa)) > 0){
        p.idade = atoi(pessoa[1]);
        lseek(pessoas_file,-sizeof (Pessoa), SEEK_CUR);
        write(pessoas_file,&p,sizeof (Pessoa));
        close(pessoas_file);
        return 0;
    }

    printf("Registo não existe!\n");

    close(pessoas_file);

    return 0;
}



int main(int argc, char** argv){

    if (argc<4) return 0;

    if (strcmp(argv[1],"-i") == 0)  return addPessoa(&argv[2]);
    else if (strcmp(argv[1],"-u") == 0) return updateIdadeNome(&argv[2]);
    else if (strcmp(argv[1],"-o") == 0) return updateIdadeRegisto(&argv[2]);


    return 0;

}