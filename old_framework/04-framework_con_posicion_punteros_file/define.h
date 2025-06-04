#ifndef _DEFINE_H
#define _DEFINE_H

#define CLAVEBASE 33
#define ROJO 0
#define VERDE 1
#define TAMANO 30
#define COLOR 10

typedef struct medicamento {
    int tipo;
    char color[COLOR+1];
    char sistema[1+1];
}med;

#endif
