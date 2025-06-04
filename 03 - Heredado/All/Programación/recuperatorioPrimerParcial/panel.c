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
	
	/*declaracion variables*/

	int id_semaforo;
	int contador;
	int puntosMax;
	FILE *archivo;
	struct equipoPingPong equipos[2];
	char palabra_clave_archivo1[60];
	char palabra_clave_archivo2[60];

	/*Iniciacion algunas variables*/

	id_semaforo = creo_semaforo();
	contador=0;
	inicia_semaforo(id_semaforo,VERDE);
	puntosMax=11;
	strcpy(equipos[0].nombreEquipo,"Japon");
	strcpy(equipos[1].nombreEquipo,"Argentina");
	equipos[0].puntos = 0;
	equipos[1].puntos = 0;

	sprintf(palabra_clave_archivo1,"Punto_de_%s",equipos[0].nombreEquipo);
	sprintf(palabra_clave_archivo2,"Punto_de_%s",equipos[1].nombreEquipo);

	/* Codigo */

	
	
	while(contador != puntosMax){

		
		
		espera_semaforo(id_semaforo);
		system("clear");
		printf("\n*********************************");
		printf("\nEl marcador se encuentra:");
		
		/*Verifico a traves de una palabra clave, cuantos puntos hizo cada equipo*/
		/*De esta forma procedo a mostrar el marcador*/

		archivo = fiAbrirArchivo("equipos.txt","r");
		equipos[0].puntos = inContarAciertosLectura(archivo,palabra_clave_archivo1,equipos[0].puntos);
		voCerrarArchivo(archivo);
		archivo = fiAbrirArchivo("equipos.txt","r");
		equipos[1].puntos = inContarAciertosLectura(archivo,palabra_clave_archivo2,equipos[1].puntos);
		voCerrarArchivo(archivo);
		
		printf("\n%s %d - %d %s",equipos[0].nombreEquipo,equipos
[0].puntos,equipos[1].puntos,equipos[1].nombreEquipo);
		
		/*Verifico si termino el partido, si esto ocurre le mando al proceso equipo que finalice */
		printf("\n*********************************\n");
		
		if(equipos[0].puntos == puntosMax || equipos[1].puntos == puntosMax){
			printf("\n*********************************");
			printf("\nTerminooo el partido\n");
			printf("\n Marcador Final: ");
			printf("\n%s %d - %d %s",equipos[0].nombreEquipo,equipos[0].puntos,equipos[1].puntos,equipos[1].nombreEquipo);
			printf("\n*********************************");
			archivo = fiAbrirArchivo("equipos.txt","a");
			inEscribirLinea(archivo,"FINAL");
			voCerrarArchivo(archivo);
			contador=puntosMax;
			
		}
		

		/*Como mi inContarAciertosLectura funciona como acumuluador, lo debo reiniciar cada iteracion*/
		equipos[0].puntos = 0;
		equipos[1].puntos = 0;
		
		

		levanta_semaforo(id_semaforo);

		usleep(500*1000);

	}
	
	
	return 0;

}
