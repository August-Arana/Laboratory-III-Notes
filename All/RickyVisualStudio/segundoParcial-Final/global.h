#ifndef _GLOBAL
#define _GLOBAL

#include "def.h"

/*Para el tp de cajero*/

struct tipo_dato
{
    int cajero;
    int importe;
    int cheque;
    int listo;
};



/*Struct para tp n7*/

struct cliente
{
	int saldo;
	char id_cliente[20];
	int numero_cajero;

};



#endif
