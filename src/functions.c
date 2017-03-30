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

void crear_hijos(int cantidad, int flag)
{
	int i;
	int pid_actual = 2; //Valor cualquiera solo para entrar al if
	int pid_flag = 0; //Valor para indicar que un pid ya se mostro y que no se repita su mensaje

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
