#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "definiciones.h"
#include "clave.h"
#include "semaforo.h"

int main(int argc, char *argv[])
{
    char nombre_producto[LARGO_NOMBRE_PRODUCTO];
    int precio_producto;
    int total_pagar;
    char archivo[20];
    int nro_cajero;
    FILE *lote;

    int id_semaforo;

    if (argc != 2)
    {
        printf("Cantidad de argumentos invalidos: especificar el numero de cajero.\n");
        return 0;
    }

    nro_cajero = atoi(argv[1]);

    sprintf(archivo, "cajero%d.dat", nro_cajero);

    id_semaforo = creo_semaforo(nro_cajero - 1);

    while (1)
    {
        espera_semaforo(id_semaforo);
        lote = fopen(archivo, "r");
        if (lote != NULL)
        {
            total_pagar = 0;
            while (!feof(lote))
            {
                fscanf(lote, "%s\t%d\n", nombre_producto, &precio_producto);
                if (nombre_producto[0] == '-')
                {
                    /* termino la carga de un comprador */
                    printf("El comprador debera abonar: $ %d\n", total_pagar);
                    total_pagar = 0;
                }
                else
                {
                    printf("Cobrando %s $ %d\n", nombre_producto, precio_producto);
                    total_pagar += precio_producto;
                }
            }

            fclose(lote);
            /* borro el archivo */
            remove(archivo);
        }
        else
        {
            perror("Error al abrir el archivo.");
        }

        levanta_semaforo(id_semaforo);
        usleep(INTERVALO_CHEQUEO * 1000);
    }
}
