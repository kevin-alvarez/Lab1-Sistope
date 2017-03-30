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
  int cantHijos, mflag, flag_padre;
  proc *hijos;

  call_getopt(argc, argv, &cantHijos, &mflag);
  printf("%i - %i\n", cantHijos, mflag);
  hijos = crear_hijos(cantHijos, mflag);
  printf("padre...\n");
  getc(stdin);
  return 0;
}
