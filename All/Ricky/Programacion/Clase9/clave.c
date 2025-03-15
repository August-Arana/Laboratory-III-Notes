#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <clave.h>
#include <def.h>

key_t creo_clave(){

	key_t clave;
	clave = ftok("/bin/cat",CLAVE_BASE);
	if(clave == (key_t)-1){

		printf("No se pudo conseguir la Clave\n");
		exit(0);		
	
	}

	return clave;

}
