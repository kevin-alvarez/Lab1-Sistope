#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "functions.h"

int isInt(char *number){
  int i, c;

  for(i=0; i<strlen(number); i++){
    c = number[i];
    if(c < 48 || c > 57 || c == 0){
      return 1;
    }
  }
  return 0;
}

void nuevoSigint(int num_senal)
{

	//Obtengo el pid del proceso actual y hago el print del mensaje
   	int pid_actual = (int)getpid(2);
   	printf("Soy el hijo con pid: %i, y estoy vivo aun", pid_actual);

   	//Ahora tengo que cambiar el Sigint por el default
   	signal(SIGINT, defaultSigint);

}

void defaultSigint(int num_senal)
{
	//aqui va el default
	kill(getpid(), sig);
}

lista *crear_lista(int pid, int hijo) {
	lista *L = (lista*)malloc(sizeof(lista));
	L->sgte = NULL;
	L->pid = pid;
	L->hijo = hijo;
	L->contador = 0;
	return L;
}

void lista_add(lista *L, int hijo, int pid) {
	lista *aux = L;
	while (aux->sgte != NULL) {
		aux = aux->sgte;
	}
	aux->sgte = (lista*)malloc(sizeof(lista));
	aux->sgte->pid = pid;
	aux->sgte->hijo = hijo;
	aux->sgte->sgte = NULL;
}
