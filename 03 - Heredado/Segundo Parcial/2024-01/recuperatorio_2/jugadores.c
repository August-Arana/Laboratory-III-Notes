#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "aleatorios.h"
#include "colas.h"
#include "memoria.h"
#include "defs.h"
#include "thread.h"

/**
 * Sincroniza el arranque de los procesos
 */
void sincronizar_arranque(int *id_memoria_sync, char *sync) {
    /* Sincronizar los procesos para empezar al mismo tiempo */
    sync = (char *) crear_memoria(sizeof(char) * 2, id_memoria_sync, CLAVE_IPC);
    sync[0] = 1;
    printf("Esperando por cancha");
    while (!sync[1]) {
        sleep(1);
        printf(".");
        fflush(stdout);
    }
    printf("\n - Arrancando el proceso\n");
    fflush(stdout);
}


int main(int argc, char *argv[]) {
    int id_memoria_sync;
    char *sync = NULL;
    int id_cola_mensajes;
    t_thread *jugadores;
    int i;
    pthread_mutex_t mutex;
    pthread_t *hilos;

    inicializar_semilla_random();

    /* Cola de mensajes */
    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_IPC);

    sincronizar_arranque(&id_memoria_sync, sync);

    /* Hilos */
    hilos = (pthread_t *) malloc(sizeof(pthread_t) * JUGADORES_SIZE);

    /* Mutex */
    pthread_mutex_init(&mutex, NULL);

    /* Inicializar los datos de los jugadores */
    jugadores = (t_thread *) malloc(sizeof(t_thread) * JUGADORES_SIZE);
    for (i = 0; i < JUGADORES_SIZE; i++) {
        jugadores[i].id_jugador = i;
        memset(jugadores[i].nombre, 0, sizeof(char) * BUFFER_SIZE);
        jugadores[i].id_cola_mensajes = id_cola_mensajes;
        jugadores[i].mutex = mutex;
        jugadores[i].puntos = 0;
    }
    /* Argentina */
    strcpy(jugadores[0].nombre, JUGADOR_ARG);
    /* Japon */
    strcpy(jugadores[1].nombre, JUGADOR_JPN);

    /* Correr threads y esperarlos */
    for (i = 0; i < JUGADORES_SIZE; i++) {
        pthread_create(&hilos[i], NULL, thread_func, (void *) &jugadores[i]);
    }
    for (i = 0; i < JUGADORES_SIZE; i++) {
        pthread_join(hilos[i], NULL);
    }

    /* Liberar recursos */
    free(jugadores);
    free(hilos);
    liberar_memoria(sync, id_memoria_sync);


    return (0);
}
