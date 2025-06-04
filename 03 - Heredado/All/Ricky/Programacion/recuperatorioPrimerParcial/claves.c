#include "stdlib.h"
#include "stdio.h"
#include "claves.h"
#include "sys/ipc.h"
#include "def.h"

key_t creo_clave(int r_clave)
{


	key_t clave;
	clave = ftok ("/bin/ls", 33);
	if (clave == (key_t)-1){
		printf("No puedo conseguir clave semaforo, mem compartida, etc. \n");
		exit(0);
	}
	return clave;


}
