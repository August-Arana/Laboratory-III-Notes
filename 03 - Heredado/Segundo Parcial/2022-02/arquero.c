#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "definiciones.h"
#include "clave.h"
#include "aleatorios.h"
#include "colas.h"
#include "memoria.h"

int main(int argc, char *argv[])
{
    mensaje msg;
    int id_cola_mensajes;
    int i = 0;
    Eventos resultado;
    char *sincro;
    int id_memoria_sincro;

    sincro = (char *)creo_memoria(sizeof(char) * 2, &id_memoria_sincro, CLAVE_BASE);

    sincro[0] = 1;
    puts("Esperando pateadores...");
    while (!sincro[1])
    {
        usleep(200);
    }

    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
    borrar_mensajes(id_cola_mensajes);
    inicializar_aleatorios();

    while (i < CANTIDAD_PATEADORES)
    {
        recibir_mensaje(id_cola_mensajes, MSG_ARQUERO, &msg);
        if (msg.int_evento == EVT_TIRO)
        {
            printf("Tiro recibido.\n");
            resultado = generar_aleatorio(EVT_GOL, EVT_FUERA);
            usleep(ESPERA_JUGADOR * 1000);
            enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_ARQUERO, resultado, "");
            i++;
        }
    }

    libero_memoria(sincro);
    borro_memoria(id_memoria_sincro);

    return 0;
}
