#include "stdio.h"
#include "stdlib.h"
#include "funciones.h"
#include "def.h"
#include "string.h"
#include "archivo.h"
#include "semaforos.h"
#include "unistd.h"
#include "time.h"






int main(int arg,char *argv[]){
	
	/* variables */

	int id_semaforo;
	char mensajeAnote[60];
	char mensajeErre[60];
	struct equipoPingPong equipos[1];
	int numeroAlAzar;
	int cantidadPuntosMax;
	int cantidadPuntosActual;
	int bufferConfirmar;
	FILE *archivo;

	/*Inicializacion de variables*/

	id_semaforo = creo_semaforo();
	inicia_semaforo(id_semaforo,ROJO);
	numeroAlAzar=0;
	cantidadPuntosMax=1;
	cantidadPuntosActual=0;
	bufferConfirmar=0;
	strcpy(equipos[0].nombreEquipo,argv[1]);
	sprintf(mensajeAnote,"Punto_de_%s",equipos[0].nombreEquipo);
	sprintf(mensajeErre,"Erro_%s",equipos[0].nombreEquipo);
	cantidadPuntosMax=11;

	

	/* ciclo de repeticion y funciones */

	srand(time(NULL));

	while(cantidadPuntosActual!=cantidadPuntosMax)

	{
		
		
		espera_semaforo(id_semaforo);
		
		/* Verifico si el partido ya termino */

		archivo = fiAbrirArchivo("equipos.txt","r");
		bufferConfirmar = inContarAciertosLectura(archivo,"FINAL",bufferConfirmar);
		voCerrarArchivo(archivo);
		
		/*Si encuentra la palabra "FINAL" en el archivo, quiere decir que el partido termino*/
		/*El bufferConfirmar esta definidi como 0. De encontrar la palbra FINAL pasara a ser 1*/
		
		if(bufferConfirmar!=0)
		{
			printf("\nBuen partido");
			cantidadPuntosActual = cantidadPuntosMax;

		}
		else
		{
			/*De no terminar el partido, el equipo tiene su tiro*/
			/*El numero al azar se limpia antes de cada tiro*/
			numeroAlAzar=0;
		
	
			/*Logica para definir si el equipo metio punto*/
			
			
			numeroAlAzar=inDevolverAleatorio(1,2);

			if(numeroAlAzar==1)
			{
				printf("\nMeti punto");
				equipos[0].puntos += 1;
				archivo = fiAbrirArchivo("equipos.txt","a");
				inEscribirLinea(archivo,mensajeAnote);
				voCerrarArchivo(archivo);
				cantidadPuntosActual++;
			
		
			}else
			{	
				printf("\nErre mi tiro");
				archivo = fiAbrirArchivo("equipos.txt","a");
				inEscribirLinea(archivo,mensajeErre);
				voCerrarArchivo(archivo);
			
			}

		   }


		levanta_semaforo(id_semaforo);

		usleep(500*1000);

	}
	
	return 0;

}
