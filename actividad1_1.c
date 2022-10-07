#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int num = 10;
    pid_t pid, hijo_pid;
    pid = getpid();

    printf("variable sin modificar %d\n", num);
    printf("Estamos en el proceso padre:%d\n", pid);
    pid = fork();
    if (pid == -1)
    { // Se ha producido algún error
        printf("Se ha producido un error y no se ha podido crear el proceso hijo\n");
        exit(pid);
    }
    if (pid == 0)
    { // no hay error, y como el valor es 0 estamos en el proceso hijo
        num = num - 6;
        printf("Estamos en el proceso hijo\n");
        printf("El PID del proceso padre es %d\n", getppid());
        printf("Mi PID es el %d\n", getpid());
        printf("El valor de num es %d\n", num);
    }
    else
    {
        //bloqueamos el proceso hijo (ahora estamos en el proceso padre)
        hijo_pid = wait(NULL);
        num = num + 4;
        printf("Estamos en el proceso padre, mi PID es %d\n el PID de mi padre (bash) es %d\n", getpid(), getppid());
        printf("El valor de num es %d\n", num);
    }
}