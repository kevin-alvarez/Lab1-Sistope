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
        exit(1);
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

      //printf("HOLAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");

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

	 //Obtengo el pid del proceso actual y hago el print del mensaje
   	int pid_actual = (int)getpid();
    sleep(1); //Le puse un sleep para probar el orden
   	printf("Soy el hijo con pid: %i, y estoy vivo aun\n\n", pid_actual);
	 //printf("Hijo...\n");

   	//Ahora tengo que cambiar el Sigint por el default
   	signal(SIGINT, SigInt_default);

}

void SigInt_default(int num_senal)
{
	//aqui va el default
	kill(getpid(), SIGTERM);
}

void SigUsr1_new(int num_senal){
  contador += 1;
  //printf("Hola, pasaste por la SIGUSR1 nueva creada por si acaso\n");
  printf("pid: %i, y he recibido esta llamada %i veces\n\n", getpid(), contador);
}

void SigUsr2_new(int num_senal){
  //printf("Hola, pasaste por la SIGUSR2 nueva creada por si acaso\n");
  fork();
}

void SigInt_padre(int num_senal)
{
  printf("Hola, soy el papa y tambien estoy vivo \n\n");
  signal(SIGINT, SigInt_default);
}
