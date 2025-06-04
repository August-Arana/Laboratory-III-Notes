#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "definiciones.h"
#include "clave.h"
#include "aleatorios.h"
#include "colas.h"

void mostrar_estado_carrera(int *recorrido_autos, int cantidad_autos)
{
    int i;
    printf("Estado carrera: ");
    for (i = 0; i < cantidad_autos; i++)
    {
        printf("%2d: %3dm, ", i + 1, recorrido_autos[i]);
    }

    printf("\n");
}

int main(int argc, char *argv[])
{
    mensaje msg;
    int id_cola_mensajes;
    int i = 0;
    int largo_cicuito;
    int *recorrido_autos;
    int cantidad_autos;
    int condicion;
    int metros_recorridos;
    int numero_auto;
    char mensaje[LARGO_MENSAJE];

    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
    borrar_mensajes(id_cola_mensajes);
    inicializar_aleatorios();
    largo_cicuito = generar_aleatorio(LARGO_MINIMO_CIRCUITO, LARGO_MAXIMO_CIRCUITO);

    printf("Largo del circuito: %dm\n", largo_cicuito);

    /*espero mensaje con la cantidad de autos*/
    condicion = 1;
    while (condicion)
    {
        recibir_mensaje(id_cola_mensajes, MSG_CIRCUITO, &msg);
        if (msg.int_evento == EVT_AUTOS)
        {
            cantidad_autos = atoi(msg.char_mensaje);
            condicion = 0;
        }
    }

    printf("Cantidad de autos: %d\n", cantidad_autos);

    /*inicializo la estructura donde guarda las diastancias y arranco la carrera*/

    recorrido_autos = (int*)malloc(sizeof(int) * cantidad_autos);

    for (i = 0; i < cantidad_autos; i++)
    {
        recorrido_autos[i] = 0;
        enviar_mensaje(id_cola_mensajes, MSG_AUTOS + i, MSG_CIRCUITO, EVT_INICIO, "");
    }

    condicion = 1;
    while (condicion)
    {
        recibir_mensaje(id_cola_mensajes, MSG_CIRCUITO, &msg);
        if (msg.int_evento == EVT_AVANZA)
        {
            metros_recorridos = atoi(msg.char_mensaje);
            numero_auto = msg.int_rte - MSG_AUTOS;
            recorrido_autos[numero_auto] += metros_recorridos;
            mostrar_estado_carrera(recorrido_autos, cantidad_autos);
            if (recorrido_autos[numero_auto] >= largo_cicuito)
            {
                printf("Auto ganador: %d\n", numero_auto + 1);

                sprintf(mensaje, "%d", numero_auto);
                for (i = 0; i < cantidad_autos; i++)
                {
                    enviar_mensaje(id_cola_mensajes, MSG_AUTOS + i, MSG_CIRCUITO, EVT_BANDERIN, mensaje);
                }

                condicion = 0;
            }
            else
            {
                enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_CIRCUITO, EVT_AVANZA, "");
            }
        }
    }

    return 0;
}
