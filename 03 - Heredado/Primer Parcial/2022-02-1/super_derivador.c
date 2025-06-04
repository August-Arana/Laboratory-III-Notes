#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "definiciones.h"
#include "clave.h"
#include "aleatorios.h"
#include "semaforo.h"
#include "consola.h"
#include "producto.h"

int main(int argc, char *argv[])
{
    char cadena[LARGO]; /* Un array lo suficientemente grande como para guardar la línea más larga del fichero */
    char archivo[20];
    FILE *lote;
    int i, cantidad_productos_comprador;
    producto lote_productos[LARGO_ARREGLO_PRODUCTOS];
    int cajero_a_enviar_comprador;

    int id_semaforo[CANTIDAD_CAJEROS];

    for (i = 0; i < CANTIDAD_CAJEROS; i++)
    {
        id_semaforo[i] = creo_semaforo(i);
        inicia_semaforo(id_semaforo[i], VERDE);
    }
    

    while (1)
    {
        /* cargo los productos */
        cantidad_productos_comprador = 0;
        do
        {
            printf("Ingrese nombre del producto: ");
            scanf("%s", lote_productos[cantidad_productos_comprador].nombre);
            printf("Ingrese precio del producto: ");
            scanf("%d", &(lote_productos[cantidad_productos_comprador].precio));
            cantidad_productos_comprador++;
        } while (preguntar_si_no("Desea cargar otro producto?"));

        /* decide a que cajero enviar */
        if (cantidad_productos_comprador <= MAXIMA_CANTIDAD_PRODUCTOS_CAJERO_1)
            cajero_a_enviar_comprador = 1;
        else if (cantidad_productos_comprador <= MAXIMA_CANTIDAD_PRODUCTOS_CAJERO_2)
            cajero_a_enviar_comprador = 2;
        else
            cajero_a_enviar_comprador = 3;

        printf("%d productos. Enviando al cajero %d.\n", cantidad_productos_comprador, cajero_a_enviar_comprador);
        sprintf(archivo, "cajero%d.dat", cajero_a_enviar_comprador);

        /* espero que se libere el cajero */
        espera_semaforo(id_semaforo[cajero_a_enviar_comprador - 1]);
        lote = fopen(archivo, "a");
        if (lote != NULL)
        {
            for (i = 0; i < cantidad_productos_comprador; i++)
            {
                sprintf(cadena, "%s\t%d\n", lote_productos[i].nombre, lote_productos[i].precio);
                printf("%s", cadena);
                fprintf(lote, "%s", cadena);
            }

            /* agrego separador de comprador */
            fprintf(lote, "-\t0\n");

            fclose(lote);
        }
        else
        {
            perror("Error al abrir el achivo");
        }

        levanta_semaforo(id_semaforo[cajero_a_enviar_comprador - 1]);

        if (!preguntar_si_no("Desea cargar otro comprador?"))
            return 0;
    }
}
