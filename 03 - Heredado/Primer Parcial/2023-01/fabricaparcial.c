#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>
#include <time.h>
#include <sys/shm.h>
#define ROJO 0
#define VERDE 1
#define HASHSEMAFORO 33
#define HASHMEMORIA1 34
#define HASHMEMORIA2 35
#define CANTIDADMEMORIA 4
#define TIMESLEEP 1
#define TIMESUSLEEP 1500


struct stock
{
	int codigo ; 	//del 1 al 4
	int cantidad;	
};


key_t creo_clave(int hash)
{
  key_t clave = ftok("/bin/ls",hash); 
  if(clave == (key_t)-1)
  {
      printf("Error no puedo conseguir clave \n");
      exit(0);
  }
  return clave;
}

int creo_semaforo(int cuantos)
{
  int semaforoid = -1;
  printf("inicio creo semaforo \n");
  key_t clave = creo_clave(HASHSEMAFORO);
  printf("creo clave \n");
  semaforoid = semget(clave,cuantos,0600|IPC_CREAT); 
  printf("obtengo semaforoid \n");
  printf("%d \n",semaforoid);
  if(semaforoid == -1)
  {
      printf("Error: no puedo crear semaforo \n");
      exit(0);
  }
  return semaforoid;
}

void inicio_semaforo(int semaforoid, int cual,int valor)
{
    semctl(semaforoid,cual,SETVAL,valor);
    printf("Inicio Semaforo \n");
}

void levanta_semaforo(int semaforoid,int cual)
{
    struct sembuf operacion;
    printf("Levanta Semaforo \n");
    operacion.sem_num = cual;
    operacion.sem_op = 1; //incrementa el semaforo en 1
    operacion.sem_flg = 0;
    semop(semaforoid,&operacion,1);
}

void espera_semaforo(int semaforoid,int cual)
{
    struct sembuf operacion;
    printf("Espera SEMAFORO \n");
    operacion.sem_num = cual;
    operacion.sem_op = -1; //decrementa el semaforo en 1
    operacion.sem_flg = 0;
    semop(semaforoid,&operacion,1);
}

int creo_id_memoria()
{
	int memoriaid;
	memoriaid = shmget (creo_clave(HASHMEMORIA1), sizeof(struct stock)*CANTIDADMEMORIA, 0777 | IPC_CREAT);  
	
	if (memoriaid == -1)
	{
		printf("No consigo id para memoria compartida \n");
		exit (0);
	}
	return memoriaid;
}

struct stock* creo_memoria(int memoriaid)
{
	struct stock* memoria;
	memoria = (struct stock*)shmat(memoriaid, (char *)0, 0);
	printf("creo memoria compartida \n");
	if (memoria == NULL)
	{
		printf("No consigo memoria compartida \n ");
		exit (0);
	}
	return memoria;
}
// shmdt ((char*)memoria);
// shmctl (memoriaid, IPC_RMID, (struct shmid_ds *)NULL);
// ipcs
// ipcrm -m numero



int main(int argc, char *argv[])
{
 int memoriaid;
 int semaforoid;
 int vehiculoid=0;
 int i =0;
 struct stock *memoria;
 struct stock m[4];
 semaforoid = creo_semaforo(1);
 memoriaid = creo_id_memoria();
 memoria = creo_memoria(memoriaid);
 inicio_semaforo(semaforoid,0,VERDE);
 
 srand(time(NULL));

 //Inicializo 
 for(i=1;i<=4;i++)
 {
		memoria[i].codigo = 0;
		memoria[i].cantidad = 0;
 }

 while(1)
 {
	vehiculoid = rand() % 4 + 1;
	printf("Vehiculo a crear ");
	printf("%d",vehiculoid);
	printf("\n");
	sleep(TIMESLEEP);

	espera_semaforo(semaforoid,0);

	if(memoria[vehiculoid].cantidad < 10)
	{
		 int cantidad = memoria[vehiculoid].cantidad;
		 cantidad = cantidad + 1;
	     memoria[vehiculoid].cantidad = cantidad;
		 m[vehiculoid].cantidad = cantidad+1;
		 printf("hay de ese vehiculo ");
		 printf("%d",cantidad);
		 printf("\n");
	}
    else
    {
		printf("No se fabrico por superar los 10");
    }
    
    levanta_semaforo(semaforoid,0);
    
 };



	return 0;
}

