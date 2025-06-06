#include "archivos.h"
#include "cola.h"
#include "define.h"
#include "global.h"
#include "memoria.h"
#include "pthread.h"
#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
/*  */

void *ThreadAnimales(void *parametro)
{
  /* Variables comunes */
  int *done;
  int avance;
  char especie[15];
  int pasos_desde;
  int pasos_hasta;

  /* Variables de mensajes */
  mensaje msg;
  char mensaje_final[LONGITUD];

  /* Variables de hilos */
  ani *datos_thread = (ani *)parametro;
  int id_animal;
  int id_cola_mensajes;

  /* Asignacion de variables */
  id_animal = datos_thread->id_animal;
  id_cola_mensajes = datos_thread->id_cola_mensajes;
  done = datos_thread->terminar;
  
  /* Vacio el contenido de variables */
  memset(especie, 0x00, sizeof(especie));

  if (id_animal == 0)
  {
    strcpy(especie, "conejo");
    pasos_desde = 4;
    pasos_hasta = 9;
  }
  else if (id_animal == 1)
  {
    strcpy(especie, "gato");
    pasos_desde = 1;
    pasos_hasta = 10;
  }
  else
  {
    strcpy(especie, "perro");
    pasos_desde = 3;
    pasos_hasta = 8;
  }

  printf("\nSoy el %s\n", especie);
  /* enviar_mensaje: id_cola, destinatario, remitente(yo), evento, char_mensaje
   */
  /* recibir_mensaje:id_cola, destinatario(yo), mensaje */

  while ((*done) == 0)
  {
    /* El thread se queda esperando mensaje, cuando le llegue un mensajem recien
     * ahi hace un lock de mutex, con esto evito que el mutex quede bloqueado
     * antes de que llegue un mensaje fuera al revez, primero se bloquea el
     * mutex y el thread bloquea al resto de los threads
     * */
    recibir_mensaje(id_cola_mensajes, MSG_JUGADOR + id_animal, &msg);
    printf("Soy el %s, recibi un mensaje\n", especie);
    pthread_mutex_lock(&mutex);

    /* Veo que hay adentro del mensaje */

    switch (msg.int_evento)
    {

    case EVT_CORRO:
      /* Elijo pasos al azar */

      avance = inNumeroAleatorio(pasos_desde, pasos_hasta);
      /* enviar_mensaje: id_cola, destinatario, remitente(yo), evento, char_mensaje
       */
      printf("%s\n", msg.char_mensaje);
      sprintf(mensaje_final, "%d", avance);
      enviar_mensaje(id_cola_mensajes, MSG_PISTA, MSG_JUGADOR + id_animal,
                     EVT_CORRO, mensaje_final);
      break;

    case EVT_FIN:
      printf("Soy el %s\n", especie);
      printf("%s\n", msg.char_mensaje);
      *done = 1;
      break;

    default:
      printf("\nEvento sin definir\n");
      break;
    }

    sleep(1);

    pthread_mutex_unlock(&mutex);

    sleep(1);
  };

  pthread_exit((void *)"Listo");
}
