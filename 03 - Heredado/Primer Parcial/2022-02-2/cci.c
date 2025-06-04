#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "definiciones.h"
#include "clave.h"
#include "semaforo.h"
#include "consola.h"

void leer_panel(int id_semaforo);
void escribir_panel(int id_semaforo);

int main(int argc, char *argv[])
{
    int salir = 0;
    int id_semaforo;
    int opcion;

    id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, VERDE);

    while (!salir)
    {
        /*muestro el menu*/
        opcion = consultar_opcion("1: Leer Panel\n2: Escribir Panel\n3: Salir\nElija una opcion: ", 3);
        switch (opcion)
        {
        case 1:
            leer_panel(id_semaforo);
            break;
        case 2:
            escribir_panel(id_semaforo);
            break;
        case 3:
            salir = 1;
            break;

        default:
            break;
        }
    }

    return 0;
}
