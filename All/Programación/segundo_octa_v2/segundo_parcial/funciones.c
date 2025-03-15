#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "time.h"
#include "unistd.h"

int num=0;

int inDevolverAleatorio(int inDesde,int inHasta)
{
	num = (rand()%(inHasta-inDesde+1))+inDesde;
	return num;
}



int *inDevolverAleatorioSinRepetir(int inDesde, int inHasta,int inCantidadAleatorios){
	int entero=0;
	int x=0,i=0,aciertos=0;
	int *valores;
	
	srand(time(0));

	if(inCantidadAleatorios > (inHasta-inDesde)){
		printf("EROR: no se puede obtener %d aleatorios con los valores ingresados\n",inCantidadAleatorios);
		return NULL;
	}else{
		valores = malloc(inCantidadAleatorios * sizeof(int));
		
		while(x<inCantidadAleatorios){
			entero=inDevolverAleatorio(inDesde,inHasta);
			printf("%d\n",entero);
			for(i=0;i<x;i++){
				if(entero==valores[i]){
					aciertos++;
				}
			}
			if(aciertos==0){
				valores[x]=entero;
				x++;
			}
			aciertos=0;
			sleep(1);
				
		}

	}

	return valores;

}
