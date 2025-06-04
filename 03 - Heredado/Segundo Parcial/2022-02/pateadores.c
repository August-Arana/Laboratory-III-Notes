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

void *funcion_pateador(void *parametro);

int main(int argc, char *argv[])
{
    char *sincro;
    int id_memoria_sincro;
    pthread_t *id_hilos;
    pthread_attr_t atributos;
    pthread_mutex_t mutex;
    int id_cola_mensajes;
    int i;
    /*parametros para pasar a los pateadores*/
    t_juego *pateadores;

    sincro = (char *)creo_memoria(sizeof(char) * 2, &id_memoria_sincro, CLAVE_BASE);

    sincro[1] = 1;
    puts("Esperando arquero...");
    while (!sincro[0])
    {
        usleep(200);
    }

    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
    pthread_mutex_init(&mutex, NULL);
    pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);

    /* alojo la memoria para los identificadores de threads y los pateadores */
    id_hilos = (pthread_t *)malloc(sizeof(pthread_t) * CANTIDAD_PATEADORES);
    pateadores = (t_juego *)malloc(sizeof(t_juego) * CANTIDAD_PATEADORES);

    /* por cada pateador inicializo la estructura con los datos e inicio el thread
       pasando el puntero a la estructura del pateador */
    for (i = 0; i < CANTIDAD_PATEADORES; i++)
    {
        pateadores[i].id_cola_mensajes = id_cola_mensajes;
        pateadores[i].resultado_tiro = 0;
        pateadores[i].mutex = &mutex;
        pateadores[i].nro_jugador = i;
        if (pthread_create(&id_hilos[i], &atributos, funcion_pateador, &pateadores[i]))
        {
            perror("No puedo crear thread");
        }
    }

    /* espero a que finalizen todos los threads */
    for (i = 0; i < CANTIDAD_PATEADORES; i++)
    {
        pthread_join(id_hilos[i], NULL);
    }

    /* muestro los resultados */
    printf("\nResultados:\n");
    for (i = 0; i < CANTIDAD_PATEADORES; i++)
    {
        printf("Jugador %d: ", i + 1);
        switch (pateadores[i].resultado_tiro)
        {
        case EVT_GOL:
            printf("Gol.\n");
            break;
        case EVT_PALO:
            printf("Palo.\n");
            break;
        case EVT_TRAVESANO:
            printf("Travesano.\n");
            break;
        case EVT_FUERA:
            printf("Afuera.\n");
            break;
        default:
            break;
        }
    }

    libero_memoria(sincro);

    /* libero la memoria alojada para los hilos y los pateadores */
    free(id_hilos);
    free(pateadores);
    return 0;
}
