#ifndef _DEFINE_H
#define _DEFINE_H

#define CLAVEBASE 33
#define CLAVEBASE2 34
#define ROJO 0
#define VERDE 1
#define LARGO 100
#define CANTIDAD_PARTIDA 10
#define INTERVALO_PRODUCTO 500
#define INTERVALO_PARTIDA 1000

typedef struct dato{
    int numero;
    char letra;
}dat;

typedef struct necesaryMemory {
    int bandera;
    dat misDatos[10];
}

#endif
