#include "stdio.h"
#include "stdlib.h"
#include "funciones.h"
#include "def.h"
#include "string.h"
#include "archivos.h"
#include "semaforo.h"
#include "unistd.h"
#include "time.h"


int main( int arg, char *argv[] ){

int id_semaforo;
char mensajeAvion[100+1];
struct avion aerolinea[1];
int confirmar=0;
int i=0;
int n=0;
n=atoi(argv[1]);

aerolinea[0].nro_avion=n;

id_semaforo = creo_semaforo();
srand(time(NULL));

while(i!=1){

    espera_semaforo(id_semaforo);

    inAbrirArchivo("vuelos.txt","r");
    confirmar=inContarAciertosLectura("\nFin de los Vuelos",confirmar);
    voCerrarArchivo();
    if(confirmar!=0){
        printf("\nVuelos Cerrados");
        i=1;
    }else{

        inAbrirArchivo("vuelos.txt","w");
        printf("\nIngrese Ciudad: ");
        scanf("%s",aerolinea[0].ciudad);
        sprintf(mensajeAvion,"Número de Avion: %d, Destino del Avion: %s\n",aerolinea[0].nro_avion,aerolinea[0].ciudad);
        inEscribirArchivo(mensajeAvion);
        voCerrarArchivo;


    }

    levanta_semaforo(id_semaforo);
    usleep(TIEMPO_ESPERA);


}


return 0;

}
