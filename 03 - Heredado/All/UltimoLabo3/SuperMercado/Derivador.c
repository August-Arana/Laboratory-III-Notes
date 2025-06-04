#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include "time.h"
#include "pthread.h"
#include "clave.h"
#include "def.h"
#include "global.h"
#include "memoria.h"
#include "cola.h"
#include "funciones.h"
#include "hilos.h"
#include "semaforo.h"
#include "archivos.h"

int main(int arg, char *argv[]){
/* variables */
	int *memoria=NULL;
	int id_memoria;
	int id_semaforo;
	int done;
    int fin;
	int i;
    int j;
    int cont;
    int numero_caja;
    int cantproduct;
    char cadena[50];
    int precio;
    char producto[50];
    char Derivador[20];
    char mensajeCaja[100+1];
    char PagoTotal[100+1];
    char totalCajas[50];
    int caja;
    int validador;
    int total;

    productos productos [20];
	mensaje msg;
	int id_cola_mensajes;

    validador=0;
	done=0;
	i=0;
    caja=0;
    total=0;
    cantproduct = 0;
    fin = 0;
    cont = 0;


	memoria = (int*)creoMemoria(sizeof(2), &id_memoria, CLAVE_BASE);
	id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
	
	id_semaforo = creo_semaforo();
   	memoria[0] = 0;
   	inicio_semaforo(id_semaforo,VERDE);

   	espera_semaforo(id_semaforo);
   	memoria[0] = 1;
   	levanta_semaforo(id_semaforo);
    
    srand(time(NULL));

  	while (TRUE)
  	{
      		espera_semaforo(id_semaforo);
     	if (memoria[1] == 1)
     	{
         	levanta_semaforo(id_semaforo);
         	break;
     	}
      	else
      	{
         	levanta_semaforo(id_semaforo);
      	}
      	usleep(TIEMPO_ESPERA);
   	}
   
    

    srand(time(NULL));
    while (done == 0)
    {
        printf("Derivador\n");
        recibir_mensaje(id_cola_mensajes,MSG_DERIVADOR,&msg);
        numero_caja = msg.rte-2;
        if (cont <12){
            if (validador == 0) {
                cantproduct=inDevolverNumeroAleatorio(1, 20);
                
                if (cantproduct>0 && cantproduct<=5) {
                    caja = 0;
                }else if (cantproduct>5 && cantproduct<=10) {
                    caja = 1;
                }else if (cantproduct>10)
                {
                    caja = 2;
                }
                sprintf(cadena, "Caja%d.txt", caja);
                if (!inAbrirArchivo(cadena, "w")) {
                    printf("Error al abrir archivo \n");
                    continue;
                }
                
                sprintf(Derivador, "Caja: %d", caja);   
                inEscribirArchivo(Derivador);
                printf("Numero de productos: %d\n", cantproduct);
                printf("ingrese el producto : ");
                scanf("%s", producto);
                printf("ingrese el precio del producto : ");
                scanf("%d", &precio);
                for (i = 0; i < cantproduct; i++) {
                    sprintf(productos[i].Descripcion, "%s", producto);
                    productos[i].precio = precio;
                    sprintf(mensajeCaja, "\nProducto: %s - Precio: %d", productos[i].Descripcion, productos[i].precio);
                    inEscribirArchivo(mensajeCaja);
                    total = total + productos[i].precio;
                }
                    sprintf(totalCajas, "%d", total);
                    sprintf(PagoTotal, "\nTotal a pagar: %d\n", total);
                    inEscribirArchivo(PagoTotal);
                    voCerrarArchivo();
                    total=0;

                    for (i = 0; i < cantproduct; i++) {
                        productos[i].precio=0;
                        memset(productos[i].Descripcion, 0, sizeof(productos[i].Descripcion));
                    }
                    memset(mensajeCaja, 0, sizeof(mensajeCaja));
                    memset(producto, 0, sizeof(producto));
                    memset(PagoTotal, 0, sizeof(PagoTotal));
                    memset(Derivador, 0, sizeof(Derivador));
                    memset(cadena, 0, sizeof(cadena));
                    precio=0;
                    cantproduct = 0;
                    validador=1;
            }
        }
        if (cont == 12) {
            printf("Super Cerrado\n");
        }
        
    
        switch (msg.evento)
        {
        case EVT_CONSULTA:
            if (cont>=0 && cont <12) {
                if (caja ==numero_caja) {
                    enviar_mensaje(id_cola_mensajes,MSG_CAJA+numero_caja,MSG_DERIVADOR,EVT_CAJA,totalCajas);
                    validador=0;
                    memset(totalCajas,0,sizeof(totalCajas));
                }
                if (caja !=numero_caja) {
                    enviar_mensaje(id_cola_mensajes,MSG_CAJA+numero_caja,MSG_DERIVADOR,EVT_NINGUNO,"" );
                }
            }
            if (cont >= 12) {
                enviar_mensaje(id_cola_mensajes,MSG_CAJA+numero_caja,MSG_DERIVADOR,EVT_FIN,"" );
                printf("Fin\n");
                fin++;
            }
            
            break;
        
        default:
            break;
        }

        if (fin == 3) {
            done=1;
        }
        cont++;
    

    }
   
    
    voLiberar_memoria(memoria, id_memoria);
    eliminar_semaforo(id_semaforo);
	borrar_mensajes(id_cola_mensajes);
    eliminar_cola_mensajes(id_cola_mensajes);
	

    return 0;

}
