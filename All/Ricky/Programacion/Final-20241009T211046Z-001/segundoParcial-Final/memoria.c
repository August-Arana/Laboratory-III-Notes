
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"

#include "claves.h"
#include "def.h"

#include "sys/ipc.h"
#include "sys/shm.h"









void *creoMemoria(int size,int *r_id_memoria, int clave_base){

	void *ptr_memoria;
	int id_memoria;
	id_memoria = shmget(creo_clave(clave_base),size,0777 | IPC_CREAT);

	if(id_memoria == -1){
		printf("\nNo consigo ID para memoria compartida");
		exit(0);

	}

	ptr_memoria = (void *)shmat (id_memoria, (char*)0,0);

	if(ptr_memoria == NULL){
		printf("\nNo consigo memoria compartida");
		exit(0);
	
	}
	*r_id_memoria = id_memoria;
	return ptr_memoria;


}


