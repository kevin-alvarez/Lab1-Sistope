#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <wait.h>

//////// --ESTRUCTURAS-- ///////

struct proc {
	pid_t pid; //guarda el pid de ese hijo
	int index; //numero de hijo
	int contador; //guarda el contador de cuantas veces ha sido llamado
};
typedef struct proc proc;


//////// --FUNCIONES-- ////////

/*
	Funcion que hace la llamada a getopt para obtener las opciones y parametros
	ingresados por la terminal.
	@param argc cantidad de argumentos ingresados en la terminal.
	@param argv vector con los argumentos ingresados por la terminal.
	@param h parametro de salida para obtener cantidad de hijos ingresada.
	@param m parametro de salida para obtener el flag de opcion -m.
*/
void call_getopt(int argc, char** argv, int *h, int *m);

/*
  Funcion que verifica si un string representa un numero o no, entrega 0 si es
  un numero y 1 si no.
  @param number string para verificar.
	@return resultado de la verificacion.
*/
int isInt(char *number);

/*
	Explicar....
*/
proc *crear_hijos(int cantidad, int mflag);

/*
	Funcion a reemplazar el SIGINT y envia el
	mensaje pedido por el enunciado.
*/
void nuevoSigint(int);

/*
	Funcion default del SIGINT, que vuelve una vez
	ejecutado el SIGINT modificado.
*/
void defaultSigint(int);


#endif
