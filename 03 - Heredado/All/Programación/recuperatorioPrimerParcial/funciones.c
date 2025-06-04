#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "funciones.h"
#include "unistd.h"
#include "time.h"



int inDevolverAleatorio(int inDesde,int inHasta){

	int numero=0;
	numero=(rand()%(inHasta-inDesde+1))+inDesde;

	return numero;


}

int *inDevolverAleatorioNoRepetido(int inDesde,int inHasta, int inCantidadAleatorios){
	/* Variables */
	int entero=0;
	int x=0,i=0,aciertos=0;
	int *valores;

	/* Bloque de Codigo */
	srand(time(0));
	if(inCantidadAleatorios > (inHasta-inDesde)){

		printf("\nError, no se pueden obtener %i numeros aleatorios con los valores ingresados",inCantidadAleatorios);
		return NULL;
	}else{
		valores = malloc(inCantidadAleatorios * sizeof(int));


		while(x<inCantidadAleatorios){
			entero=inDevolverAleatorio(inDesde,inHasta);
			printf("\n %d",entero);
			for(i=0;i < x;i++){
			
				if(entero==valores[i]){

					aciertos=aciertos+1;

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

void mostrarArreglo(int arreglo[10],int longitudArreglo){

	int i=0;

	for(i=0;i<longitudArreglo;i++){
		
		printf("\n Numero %d: %d",i+1,arreglo[i]);
	}



}




