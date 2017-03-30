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
  int hijos, mflag;
  call_getopt(argc, argv, &hijos, &mflag);
  printf("%i - %i\n", hijos, mflag);
  crear_hijos(hijos, mflag);

  return 0;
}
