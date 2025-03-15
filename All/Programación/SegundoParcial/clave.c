#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "clave.h"
#include "sys/ipc.h"
#include "def.h"

key_t creo_clave(){

	key_t clave;
	clave = ftok("/bin/ls", CLAVE_BASE);
	if(clave == (key_t)-1){
		printf("no se puede conseguir la clave semaforo, mem compartida, etc.");
		exit(0);	
	}
	return clave;

}
