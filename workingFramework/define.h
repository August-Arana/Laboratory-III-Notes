#ifndef _DEFINE_H
#define _DEFINE_H

#define CLAVEBASE 33
#define CLAVEBASE2 34
#define ROJO 0
#define VERDE 1
#define TAMANO 30

typedef struct menu {
    int tipo;
    int postre;
    int precioTotal;
    char sistema[1+1];
}men;

typedef struct dato{
    int numero;
    char letra;
}dat;

typedef struct memoriaParaUsar {
    int bandera;
    struct dato misDatos[10];
}usar;
#endif
