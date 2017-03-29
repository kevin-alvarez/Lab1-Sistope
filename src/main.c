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
  int mflag;
  char *hvalue;

  int c, hijos;

  //Obtener parametros
  mflag = 0;
  opterr = 0;

  if(argc <= 1){
    printf("Se deben ingresar opciones (uso: -h <numero de hijos> -m)\n");
    exit(1) ;
  }

  while((c = getopt(argc, argv, "h:m")) != -1){
    switch (c) {
      case 'h':
        hvalue = optarg;
        break;
      case 'm':
        mflag = 1;
        break;
      case '?':
        if(optopt == 'h'){
          fprintf(stderr, "Opcion -h requiere un argumento.\n");
        }
        else if (isprint(optopt)) {
          fprintf(stderr, "Opcion -%c desconocida.\n", optopt);
        }
        else{
          fprintf(stderr, "Opcion desconocida '\\x%x'.\n", optopt);
        }
        return 1;
      default:
        abort();
    }
  }

  if(isInt(hvalue)){
    printf("El parametro ingresado para los hijos no es valido\n");
    exit(1);
  }
  hijos = atoi(hvalue);

  //Procedimientos

  return 0;
}
