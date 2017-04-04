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
	Procedimiento que hace la llamada a getopt para obtener las opciones y
  parametros ingresados por la terminal.
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
	Funcion que creo hijos y devuelve sus pids en un arreglo, esta función es
  llamada por el proceso padre.
  @param cantidad número de hijos a crear.
  @param mflag booleano utilizado para verificar si se ingresó la bandera -m.
  @return arreglo con los pids de los hijos creados.
*/
pid_t *crear_hijos(int cantidad, int mflag);

/*
	Procedimiento para reemplazar señal SIGINT y enviar el mensaje indicando los
  hijos vivos y sus pids.
  @param num_senal número de la señal recibida.
*/
void SigInt_new(int num_senal);

/*
	Procedimiento default de SIGINT, que mata el proceso actual.
  @param num_senal número de la señal recibida.
*/
void SigInt_default(int num_senal);

/*
  Procedimiento para reemplazar señal SIGUSR1, que aumenta en 1 en contador
  del proceso que lo ejecuta.
  @param num_senal número de la señal recibida.
*/
void SigUsr1_new(int num_senal);

/*
  Procedimiento para reemplazar señal SIGUSR2, que hace que el hijo referenciado
  cree un hijo propio.
  @param num_senal número de la señal recibida.
*/
void SigUsr2_new(int num_senal);

/*
  Procedimiento para reemplazar señal SIGINT (especificamente para el padre)
  y enviar el mensaje indicando que el padre está vivo.
  @param num_senal número de la señal recibida.
*/
void SigInt_padre(int num_senal);

/*
  Procedimiento para reemplazar señales SIGUSR1 y SIGUSR2 para que tomen su
  valor por defecto, es decir, no hacer nada.
  @param num_senal número de la señal recibida.
*/
void Sig_doNothing(int num_senal);

#endif
