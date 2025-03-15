#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "sys/ipc.h"

key_t creo_clave(){

    key_t clave;
    clave = ftok ("/bin/ls", 33);
    if (clave == (key_t)-1)
    {
        printf("No pudo conseguir clave semáforo, mem compartida, etc. \n");
        exit(0);

    }
    return 0;

}
