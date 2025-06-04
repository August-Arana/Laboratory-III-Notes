#include "stdio.h"
#include "stdlib.h"
#include "funciones.h"
#include "def.h"
#include "string.h"
#include "archivos.h"
#include "semaforo.h"
#include "unistd.h"
#include "time.h"



int main(int arg, char *argv[]) {

    int id_semaforo;
    struct producto productos[50];
    int product = 0; 
    int cantproduct = 0;
    char mensajeCaja[101];
    char Derivador[101];
    char PagoToTal[101];
    char caja[100+1];
    int ronda = 0;
    int i;
    int total = 0;
    int check=0;

    /*Variables declaradas*/

    id_semaforo = creo_semaforo();
    inicio_semaforo(id_semaforo, VERDE);

    printf("\nBienvenidos al Supermercado. \n");

    while (ronda < 5) {
        
        espera_semaforo(id_semaforo);
        while(check!=1)
        {
            printf("ingrese tipo de Productos a llevar 1 para Alimentos 2 para resto de Productos: ");
            scanf("%d", &product);
            if(product==1 || product==2 ){
                check=1;
            }
            else{
                printf("\nerror no existe ese tipo de producto\n");
            }
        }
        check=0;
        printf("ingresela cantidad de Productos que va a llevar: ");
        scanf("%d", &cantproduct);
        
        if (!inAbrirArchivo("caja.txt", "w")) {
            printf("Error al abrir archivo \n");
            levanta_semaforo(id_semaforo);
            continue;
        }
        if (product==1) {
            sprintf(caja,"Alimentos");
        }else if (product==2) {
            sprintf(caja,"Productos");
        }
        
        sprintf(Derivador, "Caja: %s", caja);   
        inEscribirArchivo(Derivador);
        for (i = 0; i < cantproduct; i++) {
            printf("ingrese el producto %d: ", i + 1);
            scanf("%s", (productos[i].nombreProducto));
            printf("ingrese el precio del producto %d: ", i + 1);
            scanf("%d", &(productos[i].precioProducto));
            sprintf(mensajeCaja, "\nProducto: %s - Precio: %i", productos[i].nombreProducto, productos[i].precioProducto);
            inEscribirArchivo(mensajeCaja);
            total = total + productos[i].precioProducto;
        }
            sprintf(PagoToTal, "\nTotal a pagar: %d", total);
            inEscribirArchivo(PagoToTal);
            total = 0;
            voCerrarArchivo();

        ronda++;
        levanta_semaforo(id_semaforo);
        usleep(TIEMPO_ESPERA);
    }

    if (inAbrirArchivo("caja.txt", "w") == FALSE) {
        printf("Error al abrir archivo \n");
    }
    inEscribirArchivo("Cerro");
    voCerrarArchivo();

    printf("\nSistema Finalizado\n");
    
    printf("\nCerrando programa...\n");
    return 0;
}
