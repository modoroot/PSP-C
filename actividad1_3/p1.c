#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

const char SALUDO[]="HELLO";
const char READY[]="READY?";

int main(void)
{
  // descriptor
  int fp;
  int p, bytesleidos;
  char buffer[10];
  char mensaje[10];

  remove("FIFO");

  p = mkfifo("FIFO", S_IFIFO | 0777); // permiso de lectura y escritura

  if (p == -1)
  {
    printf("HA OCURRIDO UN ERROR...\n");
    exit(-1);
  }
  //se construye la cola para la comunicación entre los dos p
  //procesos
  fp = open("FIFO", 0);
  //este programa quedará siempre a la espera del programa 2
  while (1)
  {
    int i=0;
    bytesleidos = read(fp, buffer, 1);
    printf("OBTENIENDO Información...");
    while (bytesleidos != 0)
    {
      printf("%1c", buffer[0]); // leo un caracter
      mensaje[i]=buffer[0];
      bytesleidos = read(fp, buffer, 1); // leo otro byte
      i++;
    }
    
    //cuando llegue aquí habrá leído todo el mensaje, 
    //ahora examinamos el mensaje
    if(strncmp(mensaje,SALUDO,sizeof(SALUDO)-1)==0){
      //responder al programa 2 con HALLO
      write(fp,"HALLO",strlen("HALLO"));
    }elseif(strncmp(mensaje,READY,sizeof(READY)-1)){
      //responde al programa 2 con OK
      write(fp,"OK",strlen("OK"));
    }elseif(strcmp(getToken(mensaje),"+")){
      
    } 
    }else{
      write(fp,"NOK",strlen("NOK"));
    }
  }
}
int sumar(int a, int b)
{
  return (a + b);
}
int multiplicar(int a, int b)
{
  return (a * b);
}