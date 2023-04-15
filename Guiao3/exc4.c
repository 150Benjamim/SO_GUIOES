#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h>

#include <string.h>

int mysystem(char* command){

    char* exec_arg[20];
    char* token = strtok(command," ");
    int i = 0;

    for (; token != NULL; i++){

        exec_arg[i] = token;
        token = strtok(NULL, " ");
    }
    exec_arg[i] = NULL;

    pid_t pid;
    int exec_ret;
    int status;

    if ((pid = fork()) == 0){
        exec_ret = execvp(exec_arg[0],exec_arg);
        _exit(exec_ret);
    }

    if (pid != -1){
        wait(&status);
        if (WIFEXITED(status))
            return WEXITSTATUS(status);
        else
            return -1;
    }

    else{
        return -1;
    }

}

int main(int argc, char** argv) {

    if (argc<2) return 0;

    char comando[124];

    strcpy(comando,argv[1]);
    for (int i = 2; i<argc; i++){
        strcat(comando, " ");
        strcat(comando,argv[i]);
    }

    mysystem(comando);

    return 0;
}
