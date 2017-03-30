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
  //printf("%i - %i\n", cantHijos, mflag);
  hijos = crear_hijos(cantHijos, mflag);

  signal(SIGINT,SigInt_padre);

  while(1){
    sleep(1);
    printf("Ingresar numero de hijo y senal a enviar (X - Y): \n");
    scanf("%i - %i", &numHijo, &numSenal);

    //printf("PID: %i", hijos[numHijo-1]);
    
    printf("La senal %i sera enviada al hijo %i\n\n", numSenal, numHijo);
    switch(numSenal)
    {
      case 15:
        kill(hijos[numHijo-1], SIGTERM);
        break;
      case 16:
        kill(hijos[numHijo-1], SIGUSR1);
        break;
      case 17:
        kill(hijos[numHijo-1], SIGUSR2);
        break;
      default:
        printf("NO ESTA ESPECIFICADA ESA SENAL\n\n");
        break;
    }
    //kill(hijos[numHijo-1], numSenal);
  }
  return 0;
}
