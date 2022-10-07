#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
const char HALLO[] = "HALLO";
const char OK[] = "OK";
const char READY[]="READY?";
int main()
{
  int fp, bytesLeidos;
  int opcion=0;
  char tecla;
  char buffer[10];
  char mensaje[10];
  fp = open("FIFO", 1);

  if (fp == -1)
  {
    printf("ERROR AL ABRIR EL FICHERO...");
    exit(-1);
  }
  // este programa en primer lugar enviará el saludo para
  // iniciar la conversación, si no obtiene respuesta
  // o la respuesta no es correcta terminará, no
  // mostrará ni siquiera el menú al usuario
  escribirEnLaCola("HELLO");
  mensaje = leerDeLaCola();
  //si llega aquí es porque el otro proceso le ha respondido
  if(strncmp(mensaje, HALLO,strlen(HALLO)-1)!=0)
    exit(-2);
  
  //si llega hasta aquí es porque el proceso 1 le ha respondido bien
  escribirEnLaCola(READY)
  mensaje = leerDeLaCola();
  if(strncmp(mensaje, READY,strlen(READY)-1)!=0)
    exit(-3);
    
  //si llega hasta aquí es porque el proceso 1 está preparado para operar
  //se debe mostrar el menú de usuario
  while (opcion!=3)
  {
    printf("1. Suma\n");
    printf("2. Multiplicación\n");
    printf("3. Salir\n");
    scanf("%d",&opcion);
    switch(opcion){
      case 1:
        //se envía el mensaje al programa 1 para iniciar la operación
        escribirEnLaCola("44+5");
        //se lee la respuesta añadida a la cola
        //se muestra el resultado includio en la respuesta
        break;
      case 2:
        break;
      case 3:
      default:
        printf("Opción incorrecta, pulse una tecla\n");
        scanf("%c",tecla);
    }
  }
  close(fp);
}
void escribirEnLaCola(char mensaje[])
{
  write(fp, mensaje, strlen(mensaje));
}
char[] leerDeLaCola();
{
  bytesLeidos = read(fp, buffer, 0);
  char mensaje[10];
  int i = 0;
  mensaje[i++]=buffer[0];
  while (bytesLeidos != 0)
  {
    bytesleidos = read(fp, buffer, 1); // leo otro byte
    mensaje[i++] = buffer[0];
  }
  return mensaje;
}