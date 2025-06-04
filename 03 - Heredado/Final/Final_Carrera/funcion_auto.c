#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "definiciones.h"
#include "colas.h"
#include "aleatorios.h"

void *funcion_auto(void *parametro)
{
    t_auto_carrera *auto_carrera;
    mensaje msg;
    int condicion;
    int avance;
    char mensaje[LARGO_MENSAJE];

    /* obtengo los datos del auto desde el parametro */
    auto_carrera = (t_auto_carrera *)parametro;

    recibir_mensaje(auto_carrera->id_cola_mensajes, MSG_AUTOS + auto_carrera->nro_auto, &msg);
    if (msg.int_evento == EVT_INICIO)
    {
        /*inicia la carrera*/
        condicion = 1;
        while (condicion)
        {
            avance = generar_aleatorio(MINIMO_AVANCE_AUTO, MAXIMO_AVANCE_AUTO);
            sprintf(mensaje, "%d", avance);
            printf("Auto %d avanza %dm\n", auto_carrera->nro_auto + 1, avance);
            enviar_mensaje(auto_carrera->id_cola_mensajes, MSG_CIRCUITO, MSG_AUTOS + auto_carrera->nro_auto, EVT_AVANZA, mensaje);
            recibir_mensaje(auto_carrera->id_cola_mensajes, MSG_AUTOS + auto_carrera->nro_auto, &msg);
            if (msg.int_evento == EVT_BANDERIN)
            {
                if (auto_carrera->nro_auto == atoi(msg.char_mensaje))
                    printf("Auto %d es el ganador\n", atoi(msg.char_mensaje) + 1);
                condicion = 0;
            }
            else
            {
                usleep(ESPERA_AUTO * 10000);
            }
        }
    }

    pthread_exit(0);
}
