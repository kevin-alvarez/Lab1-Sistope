#include "functions.h"

/*
  Laboratorio 1 - Sistemas operativos
  USACH 1-2017

  Integrantes:
  - Kevin Alvarez
  - Javier Vasquez

  Descripción:
  El presente laboratorio consiste en la creación de procesos, donde un padre,
  creará tantos hijos como se ingrese por línea de comando haciendo uso de
  "getopt". Luego, el padre podrá enviar señales a los hijos.
*/

int main(int argc, char** argv){
  int cantHijos, mflag, numHijo, numSenal;
  pid_t *hijos;
  contador = 0;

  call_getopt(argc, argv, &cantHijos, &mflag);
  hijos = crear_hijos(cantHijos, mflag);

  signal(SIGINT,SigInt_padre);//para evitar que el padre muera al hacer la señal SIGINT.

  while(1){
    sleep(1);
    printf("Ingresar numero de hijo y senal a enviar (X - Y): \n");
    scanf("%i - %i", &numHijo, &numSenal);

    if(numHijo > 0 && numHijo < cantHijos && hijos[numHijo-1] != -1){
      printf("La senal %i sera enviada al hijo %i con pid: %i\n\n", numSenal, numHijo, hijos[numHijo-1]);
      switch(numSenal)
      {
        case 15:
          kill(hijos[numHijo-1], SIGTERM);
          wait(2);//padre espera a hijo (Usado para evitar procesos zombies)
          hijos[numHijo-1] = -1;//el hijo fue eliminado.
          break;
        case 16:
          kill(hijos[numHijo-1], SIGUSR1);
          break;
        case 17:
          kill(hijos[numHijo-1], SIGUSR2);
          break;
        default:
          printf("NO ESTA ESPECIFICADA ESA SENAL.\n\n");
          break;
      }
    }else{
      printf("Hijo inexistente, el hijo ya fue eliminado o nunca fue creado, ingrese el numero de un hijo que exista.\n");
    }
  }
  return 0;
}
