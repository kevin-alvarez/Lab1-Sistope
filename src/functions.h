#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>

//////// --VARIABLES GLOBALES-- ///////
int contador;

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
pid_t *crear_hijos(int cantidad, int mflag);

/*
	Funcion a reemplazar el SIGINT y envia el
	mensaje pedido por el enunciado.
*/
void SigInt_new(int num_senal);

/*
	Funcion default del SIGINT, que vuelve una vez
	ejecutado el SIGINT modificado.
*/
void SigInt_default(int num_senal);

void SigUsr1_new(int num_senal);

void SigUsr2_new(int num_senal);

/*
	Sigint para que el padre no muera
	cuando se presiones ctrl+c
*/
void SigInt_padre(int num_senal);

void Sig_doNothing(int num_senal);

#endif
