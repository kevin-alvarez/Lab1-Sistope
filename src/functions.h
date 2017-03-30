#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>

//////// --ESTRUCTURAS-- ///////

struct list {
	int hijo; //guarda el número de hijo
	int pid; //guarda el pid de ese hijo
	int contador; //guarda el contador de cuantas veces ha sido llamado
	struct list *sgte;
};
typedef struct list lista;


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
	Funcion a reemplazar el SIGINT y envia el
	mensaje pedido por el enunciado.
*/
void nuevoSigint(int);

/*
	Funcion default del SIGINT, que vuelve una vez
	ejecutado el SIGINT modificado.
*/
void defaultSigint(int);

/*
	Crea una lista con un valor inicial.
*/
lista *crear_lista(int pid, int hijo);

/*
	Agrega un nodo al final de la lista
	con ciertos valores.
*/
void lista_add(lista *L, int hijo, int pid);

/*
	Explicar....
*/
void crear_hijos(int cantidad, int flag);


#endif
