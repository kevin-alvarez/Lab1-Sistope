#include "functions.h"

void call_getopt(int argc, char** argv, int *h, int *m){
  int c, hijos, mflag;
  char *hvalue;

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
        return;
      default:
        abort();
    }
  }

  if(isInt(hvalue)){
    printf("El parametro ingresado para los hijos no es valido\n");
    exit(1);
  }
  *h = atoi(hvalue);
  *m = mflag;
}

int isInt(char *number){
  int i, c;

  for(i=0;i<strlen(number); i++){
    c = number[i];
    if(c < 48 || c > 57 || c == 0){
      return 1;
    }
  }
  return 0;
}

void nuevoSigint(int num_senal){

	//Obtengo el pid del proceso actual y hago el print del mensaje
   	int pid_actual = (int)getpid();
   	printf("Soy el hijo con pid: %i, y estoy vivo aun", pid_actual);

   	//Ahora tengo que cambiar el Sigint por el default
   	signal(SIGINT, defaultSigint);

}

void defaultSigint(int num_senal)
{
	//aqui va el default
	kill(getpid(), SIGTERM);
}

proc *crear_hijos(int cantidad, int mflag){
	int i, j;
  proc *hijos, hijo_actual;

  hijos = (proc*)malloc(cantidad*sizeof(proc));

  for(i=0;i < cantidad;i++){
    hijo_actual.pid = fork();
    hijo_actual.index = i+1;
    if (hijo_actual.pid == 0){
      //printf("soy el hijo %i\n", i);
      while(1); //el hijo queda en espera
      break;
    }else{
      hijos[i] = hijo_actual;
      if(mflag == 1){
        printf("Numero: %i , pid:%i\n", hijos[i].index, hijos[i].pid);
      }
    }
  }

  return hijos;


/*
	//creo la cabecera de la lista
	lista *L = crear_lista(-1,-1);

	//Mensaje en caso de que el usuario haya pedido esta informacion
	if(flag == 1)
	{
		printf("Mostrando la informacion por pantala:\n");
	}

	//ciclo for para crear los hijos
	for(i=0; i < cantidad; i++)
	{
		if(pid_actual != 0)
		{
			pid_actual = fork();
			lista_add(L,(i+1),pid_actual);
		}
		if( (flag == 1)&&(pid_actual == 0)&&(pid_flag == 0) )
		{
			printf("Numero: %i, pid:%i \n", (i+1), getpid());
			pid_flag = 1; //se cambia el flag para que no se muestre el mensaje de este hijo de nuevo en otra iteracion
		}
	}


	/*Estaba probando si agregaba.

	if(pid_actual != 0)
	{
		printf("pid3: %i", L->sgte->sgte->sgte->pid);
	}*/
}
