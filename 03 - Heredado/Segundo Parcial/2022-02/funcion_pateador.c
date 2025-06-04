#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "definiciones.h"
#include "colas.h"

/* funcion para el thread del pateador */
void *funcion_pateador(void *parametro)
{
    t_juego *pateador;
    mensaje msg;

    /* obtengo los datos del jugador desde el parametro */
    pateador = (t_juego *)parametro;

    pthread_mutex_lock(pateador->mutex);

    usleep(ESPERA_JUGADOR * 1000);

    /*Tiro*/
    enviar_mensaje(pateador->id_cola_mensajes, MSG_ARQUERO, MSG_PATEADOR + pateador->nro_jugador, EVT_TIRO, "");
    /*Espero resultado*/
    recibir_mensaje(pateador->id_cola_mensajes, MSG_PATEADOR + pateador->nro_jugador, &msg);

    if (msg.int_evento == EVT_GOL)
    {
        printf("Jugador %d:  GOOOOOL\n", pateador->nro_jugador + 1);
    }
    else
    {
        printf("Jugador %d:  UFFFFF\n", pateador->nro_jugador + 1);
    }

    /*guardo el resultado*/
    pateador->resultado_tiro = msg.int_evento;

    pthread_mutex_unlock(pateador->mutex);
    pthread_exit(0);
}
