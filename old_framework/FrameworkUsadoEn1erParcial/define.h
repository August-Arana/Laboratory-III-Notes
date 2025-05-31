#ifndef _DEFINE_H
#define _DEFINE_H

#define CLAVEBASE 33
#define ROJO 0
#define VERDE 1
#define TAMANO 30

typedef struct menu {
    int tipo;
    int postre;
    int precioTotal;
    char sistema[1+1];
}men;

#endif
