#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "definiciones.h"
#include "clave.h"
#include "aleatorios.h"
#include "colas.h"

void *funcion_auto(void *parametro);

int main(int argc, char *argv[])
{
    pthread_t *id_hilos;
    pthread_attr_t atributos;
    int id_cola_mensajes;
    int i;
    int cantidad_autos;
    char mensaje[LARGO_MENSAJE];
    /*parametros para pasar a los pateadores*/
    t_auto_carrera *autos;

    /* Control de parametros recibidos*/
    if (argc != 2)
    {
        printf("Se necesita 1 argumento (cantidad de autos)\n");
        return 1;
    }
    else
    {
        cantidad_autos = atoi(argv[1]);
    }

    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);

    /*informo al circuito la cantidad de autos*/
    sprintf(mensaje, "%d", cantidad_autos);
    enviar_mensaje(id_cola_mensajes, MSG_CIRCUITO, MSG_AUTOS, EVT_AUTOS, mensaje);

    pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);

    /* alojo la memoria para los identificadores de threads y los autos */
    id_hilos = (pthread_t *)malloc(sizeof(pthread_t) * cantidad_autos);
    autos = (t_auto_carrera *)malloc(sizeof(t_auto_carrera) * cantidad_autos);

    /* por cada auto, inicializo la estructura con los datos e inicio el thread
       pasando el puntero a la estructura del auto */
    for (i = 0; i < cantidad_autos; i++)
    {
        autos[i].id_cola_mensajes = id_cola_mensajes;
        autos[i].nro_auto = i;
        if (pthread_create(&id_hilos[i], &atributos, funcion_auto, &autos[i]))
        {
            perror("No puedo crear thread");
        }
    }

    /* espero a que finalizen todos los threads */
    for (i = 0; i < cantidad_autos; i++)
    {
        pthread_join(id_hilos[i], NULL);
    }

    /* libero la memoria alojada para los hilos y los autos */
    free(id_hilos);
    free(autos);

    return 0;
}
