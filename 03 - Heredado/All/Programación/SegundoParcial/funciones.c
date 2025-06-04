#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "funciones.h"

int inDevolverAleatorio(int inDesde, int inHasta){
	return (rand()%(inDesde-inHasta+1))+inDesde;
}
