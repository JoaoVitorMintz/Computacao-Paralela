# include <stdio.h>
#include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>

int main () {

    for (int i = 0; i < 3; i++) {
        pid_t pid = fork ();
        if (pid < 0) {
            fprintf(stderr, "Fork falhou!\n"); return 1;
        } else if (pid == 0) {
            printf("Eu sou o filho! Meu PID é %d, meu pai é %d.\n", getpid(), getppid());
        } else {
            printf("Eu sou o pai! Meu PID é %d, criei o filho %d.\n", getpid(), pid);
            exit(0);
        }
    }


 return 0;
}

/*
if ( pid < 0) { // Erro
        fprintf (stderr , " Fork falhou !\n");
        return 1;

    } else if (pid == 0) { // Processo Filho
        printf ("Eu sou o filho ! Meu PID e %d, meu pai e %d.\n", getpid () , getppid ());

    } else { // Processo Pai
        printf ("Eu sou o pai! Meu PID e %d, criei o filho %d.\n", getpid () , pid);
        wait ( NULL ); // Pai espera o filho terminar
        printf ("Meu filho terminou , agora eu posso terminar .\n");

    }
*/