#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
/* gestión de señales en proceso padre */
void gestion_padre(int signal)
{
    printf("Padre recibe señal..%d\n", signal);
}
/* gestión de señales en proceso hijo */
void gestion_hijo(int signal)
{
    printf("Hijo recibe señal..%d\n", signal);
}

int main()
{
    int pid_padre, pid_hijo;
    int n = 0;
    pid_padre = getpid();
    pid_hijo = fork(); // creamos hijo

    switch (pid_hijo)
    {
    case -1:
        printf("Error al crear el proceso hijo...\n");
        exit(-1);
    case 0: // HIJO
        // tratamiento de la señal en proceso hijo
        signal(SIGUSR1, gestion_hijo);
        while (n<=3)
        {
            sleep(1);//espera 1 seg
            kill(pid_padre, SIGUSR1); // ENVIA SEÑAL AL PADRE
            n++;
        }
        kill(pid_padre, SIGKILL);//termina el proceso padre
        break;
    default: // PADRE
        // tratamiento de la señal en proceso padre
        signal(SIGUSR1, gestion_padre);
        while (1)
        {
            pause(); // padre espera hasta recibir una señal del hijo
            sleep(1);
        }
        break;
    }
    return 0;
}