#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "aleatorios.h"
#include "colas.h"
#include "defs.h"
#include "memoria.h"

/**
 * Sincroniza el arranque de los procesos
 */
void sincronizar_arranque(int *id_memoria_sync, char *sync) {
    /* Sincronizar los procesos para empezar al mismo tiempo */
    sync = (char *) crear_memoria(sizeof(char) * 2, id_memoria_sync, CLAVE_IPC);
    sync[1] = 1;
    printf("Esperando por jugadores");
    while (!sync[0]) {
        sleep(1);
        printf(".");
        fflush(stdout);
    }
    printf(" - Arrancando el proceso\n");
    fflush(stdout);
}

void informar_ganador(t_jugador jugadores[]) {
    int punto_extra;
    printf("Analizando resultados...\n");
    if (jugadores[0].turno == jugadores[1].turno) {
        punto_extra = generar_int_acotado(0, 1);
        jugadores[punto_extra].turno++;
    }

    if (jugadores[0].turno < jugadores[1].turno) {
        printf("Gano el partido %s, llego a %d puntos en %d turnos\n", jugadores[0].nombre, jugadores[0].puntos, jugadores[0].turno);
    } else {
        printf("Gano el partido %s, llego a %d puntos en %d turnos\n", jugadores[1].nombre, jugadores[1].puntos, jugadores[1].turno);
    }
}

int main(int argc, char *argv[]) {
    int id_memoria_sync;
    char *sync = NULL;
    t_jugador jugadores[JUGADORES_SIZE];
    int i, id_cola_mensajes;
    t_mensaje msg;
    int is_running = 2;
    int id_jugador;

    /* Cola de mensajes */
    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_IPC);
    borrar_mensajes(id_cola_mensajes);

    sincronizar_arranque(&id_memoria_sync, sync);

    /* Inicializar jugadores */
    for (i = 0; i < JUGADORES_SIZE; i++) {
        memset(jugadores[i].nombre, 0, sizeof(char) * BUFFER_SIZE);
        jugadores[i].puntos = 0;
        jugadores[i].turno = 0;
    }
    strcpy(jugadores[0].nombre, JUGADOR_ARG);
    strcpy(jugadores[1].nombre, JUGADOR_JPN);

    printf("Iniciando recepción de mensajes...\n");

    while (is_running) {
        /* Recibir los mensajes de los jugadores */
        if (recibir_mensaje(id_cola_mensajes, MSG_CANCHA, &msg) == -1) {
            perror("Error recibiendo mensaje");
            continue;
        }
        id_jugador = msg.remitente;

        if (msg.evento != EVT_FIN) {
            jugadores[id_jugador].turno++;
        }

        if (msg.evento == EVT_PUNTO) {
            jugadores[id_jugador].puntos++;
            printf("%s: Punto. Turno %d - Puntos totales: %d\n", jugadores[id_jugador].nombre, jugadores[id_jugador].turno, jugadores[id_jugador].puntos);
        } else if(msg.evento == EVT_FUERA) {
            printf("%s: Fuera. Turno %d - Puntos totales: %d\n", jugadores[id_jugador].nombre, jugadores[id_jugador].turno, jugadores[id_jugador].puntos);
        } else if (msg.evento == EVT_FIN) {
            printf("%s: Finalizado\n", jugadores[id_jugador].nombre);
            is_running--;
        }

        fflush(stdout);
    }
    fflush(stdout);

    informar_ganador(jugadores);

    /* Eliminar memoria compartida */
    liberar_memoria(sync, id_memoria_sync);
    borrar_cola_de_mensajes(id_cola_mensajes);

    return (0);
}
