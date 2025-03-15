#include "stdlib.h"
#include "stdio.h"
#include "clave.h"
#include "sys/ipc.h"
#include "def.h"

key_t crear_clave()
{
	key_t clave;
	clave = ftok("/bin/cat",CLAVE_BASE);
	printf("clave: %i\n",clave);
	if (clave == (key_t)-1)
	{
		printf("No se puede conseguir clave semáforo, mem compartida, etc.\n");
		exit(0);
	}
	return clave;
}
