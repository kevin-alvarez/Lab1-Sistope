#include "functions.h"

void call_getopt(int argc, char** argv, int *h, int *m){
  int c, hijos, mflag;
  char *hvalue;

  //Obtener parametros.
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
        exit(1);
      default:
        abort();
    }
  }

  //Procesar parametros.
  if(isInt(hvalue)){
    printf("El parametro ingresado para los hijos no es valido\n");
    exit(1);
  }
  //retorno de parametros por referencia.
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

pid_t *crear_hijos(int cantidad, int mflag){
	int i, j;
  pid_t *hijos, hijo_actual;

  hijos = (pid_t*)malloc(cantidad*sizeof(pid_t));

  if(mflag==1)
  {
    printf("Mostrando la información por pantalla: \n");
  }

  for(i=0;i < cantidad;i++){
    hijo_actual = fork();
    if (hijo_actual== 0){
      signal(SIGINT, SigInt_new);
      signal(SIGUSR1, SigUsr1_new);
      signal(SIGUSR2, SigUsr2_new);
      while(1); //el hijo queda en espera
      break;
    }else{
      hijos[i] = hijo_actual;
      if(mflag == 1){
        printf("Numero: %i , pid:%i\n", i+1, hijos[i]);
      }
    }
  }

  return hijos;
}

void SigInt_new(int num_senal){
   	pid_t pid_actual = getpid();
    sleep(1); //Le puse un sleep para probar el orden
   	printf("Soy el hijo con pid: %i, y estoy vivo aun\n\n", pid_actual);

   	//Ahora tengo que cambiar el Sigint por el default
   	signal(SIGINT, SigInt_default);

}

void SigInt_default(int num_senal)
{
	kill(getpid(), SIGTERM);//default signal para SIGINT
}

void SigUsr1_new(int num_senal){
  contador += 1;
  printf("pid: %i, y he recibido esta llamada %i veces\n\n", getpid(), contador);
}

void SigUsr2_new(int num_senal){
  pid_t pid_hijo;
  pid_hijo = fork();
  if(pid_hijo == 0){//Si es el hijo recien creado
    signal(SIGINT, SigInt_default);
    signal(SIGUSR1, Sig_doNothing);
    signal(SIGUSR2, Sig_doNothing);
  }
}

void SigInt_padre(int num_senal)
{
  printf("Hola, soy el Padre y estoy vivo \n\n");
  signal(SIGINT, SigInt_default);
}

void Sig_doNothing(int num_senal){
  //Para que una señal no procese ninguna instruccion.
}
