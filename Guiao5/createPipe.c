#include <sys/stat.h>

#include <stdio.h>

int main() {

    if (mkfifo("fifo",0660)==-1) {
        perror("Erro a criar FIFO");
        return -1;
    }


    return 0;
}
