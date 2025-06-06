#include "cola.h"
#include "define.h"
#include "funciones.h"
#include "memoria.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  /* Variables comunes */
  int done;
  int cantidad_pasos[3] = {0};
  int i,j;

  /* Variables de mensajes */
  int id_cola_mensajes;
  mensaje msg;

  /* Asignacion de variables */
  done = 0;
  id_cola_mensajes = creo_id_cola_mensajes(CLAVEBASE);

  /* Borrar los mensajes anteriores, para empezar de 0 */
  borrar_mensajes(id_cola_mensajes);

  /* Semaforo memoria */
  semaforo_de_memoria(1);

  /* enviar_mensaje: id_cola, destinatario, remitente(yo), evento, char_mensaje
   */
  /* recibir_mensaje:id_cola, destinatario(yo), mensaje */

  while (done == 0)
  {
    printf("Soy el la pista, le aviso a los corredores que corran\n");

    for (i = 0; i < 3; i++)
    {
      enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + i, MSG_PISTA,
                     EVT_CORRO, "Pista: Corre! Es tu turno!\n");
      recibir_mensaje(id_cola_mensajes, MSG_PISTA, &msg);
      cantidad_pasos[i] += atoi(msg.char_mensaje);

      if (msg.int_rte - 2 == 0)
      {
        printf("El conejo va %d pasos!!\n",cantidad_pasos[i]);
      }
      else if (msg.int_rte - 2 == 1)
      {
        printf("El gato va %d pasos!!\n",cantidad_pasos[i]);
      }
      else
      {
        printf("El perro va %d pasos!!\n",cantidad_pasos[i]);
      }
    }

    /* Ahora veo los pasos de cada corredor */

    for (i = 0; i < 3; i++)
    {
      if (cantidad_pasos[i] >= 30)
      {
        /* Tengo un ganador */
        done = 1;
        for(j = 0; j<3; j++){
            if(j == i){

                enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + j, MSG_PISTA, EVT_FIN, "\nGANASTE COLAPINTO!!\n");
            }else{
                enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + j, MSG_PISTA, EVT_FIN, "\nLo siento Verstappen, Perdiste!!!\n");
            }
        }
      }
    }

    usleep(3000);
  };

  printf("JUEGO TERMINADO\n");
  return 0;
}
