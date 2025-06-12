#ifndef DEFS_H
#define DEFS_H

#include <pthread.h>

#ifndef NULL
#define NULL 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define BUFFER_SIZE 100

#define ROJO 0
#define VERDE 1

#define RUTA_IPC "/tmp"
#define CLAVE_IPC 34

#define LARGO_DESCRIPCION 100
#define CANT_SEMAFORO 1

#define JUGADORES_SIZE 2
#define JUGADOR_ARG "Argentina"
#define JUGADOR_JPN "Japon"
#define META 11

#define PRODUCTOR_DESDE 50000
#define PRODUCTOR_HASTA 80000

typedef enum {
    MSG_JUGADOR1 = 0,
    MSG_JUGADOR2 = 1,
    MSG_CANCHA = 2
} t_destinos;

typedef enum {
    EVT_FUERA = 0,
    EVT_PUNTO = 1,
    EVT_FIN,
    EVT_NINGUNO
} t_eventos;

typedef struct {
    char nombre[BUFFER_SIZE];
    int puntos;
    int turno;
} t_jugador;

typedef struct {
    int id_jugador;
    int id_cola_mensajes;
    char nombre[BUFFER_SIZE];
    int puntos;
    pthread_mutex_t mutex;
} t_thread;


#endif
