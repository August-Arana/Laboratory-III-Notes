#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "defs.h"
#include "aleatorios.h"
#include "thread.h"
#include "colas.h"

void* thread_func(void* arg) {
    t_mensaje msg;
    int puntos_totales = 0, puntos;
    int turno = 0;
    t_thread *jugador = (t_thread *) arg;

    printf("%s arrancando\n", jugador->nombre);

    while (puntos_totales < META) {
        turno++;

        puntos = generar_int_acotado(EVT_FUERA, EVT_PUNTO);
        puntos_totales += puntos;

        /* El mensaje esta vacío, porque solo nos interesa mandar el evento */
        sprintf(msg.mensaje, "%d", generar_int());

        /* Bloqueamos el mutex solo para enviar el mensaje */
        /* usleep(generar_int_acotado(PRODUCTOR_DESDE, PRODUCTOR_HASTA)); */
        pthread_mutex_lock(&jugador->mutex);
        enviar_mensaje(jugador->id_cola_mensajes, MSG_CANCHA, jugador->id_jugador, puntos, msg.mensaje);
        pthread_mutex_unlock(&jugador->mutex);

        printf("%s: turno %d, puntos %d\n", jugador->nombre, turno, puntos_totales);
        fflush(stdout);

        usleep(generar_int_acotado(PRODUCTOR_DESDE, PRODUCTOR_HASTA));
    }

    /* Aviso que no envio mas mensajes */
    pthread_mutex_lock(&jugador->mutex);
    enviar_mensaje(jugador->id_cola_mensajes, MSG_CANCHA, jugador->id_jugador, EVT_FIN, msg.mensaje);
    pthread_mutex_unlock(&jugador->mutex);

    printf("%s finalizado\n", jugador->nombre);

    pthread_exit(0);
}
