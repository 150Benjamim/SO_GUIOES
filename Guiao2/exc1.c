#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */

#include <stdio.h>

int main() {

    printf("PID do processo: %d\n", getpid());
    printf("PID do processo-pai: %d\n", getppid());

    return 0;
}
