#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */


int main() {

    execlp("ls","ls","-l", (char*) NULL);

    return 0;
}
