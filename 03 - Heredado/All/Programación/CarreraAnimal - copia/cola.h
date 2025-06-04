#ifndef _COLA
#define _COLA

struct estructura_mensajes{
    long dest;
    int rte;
    int evento;
    char mensaje[100];
};

typedef struct estructura_mensajes mensaje;

int creo_id_cola_mensajes(int clave);
int enviar_mensaje(int id_cola_mensajes, long rLongDest, int rIntRte, int rIntEvento, char* rpCharMsg);
int recibir_mensaje(int id_cola_mensajes, long rLongDest, mensaje* rMsg);
int borrar_mensajes(int id_cola_mensajes);
int eliminar_cola_mensajes(int id_cola_mensajes);

#endif
