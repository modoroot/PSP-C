#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid_hijo, pid;
    pid = fork();

    if (pid == -1)
    {   //Se ha producido algún error
        printf("Se ha producido un error y no se ha podido crear el proceso hijo\n");
        exit(pid);
    }
    if (pid == 0)
    { //no hay error, y como el valor es 0 estamos en el proceso hijo
        printf("Estamos en el proceso hijo\n");
        printf("El PID del proceso padre es %d\n", getppid());
        printf("Mi PID es el %d\n", getpid());
    }
    else
    { 
        // 6. Este código sólo lo ejecuta el padre
        // estamos en proceso padre, el valor de pid>0
        pid_hijo = wait(NULL); // bloquea al procesa padre y espera al proceso hijo

printf("----------------------------------------------------------\n");
        printf("Estamos en el proceso padre, mi PID es %d\n el PID de mi padre es %d\n",
            getpid(),getppid());
        printf("Mi proceso hijo %d ha terminado\n",pid_hijo);
    }
    exit(0);
}
