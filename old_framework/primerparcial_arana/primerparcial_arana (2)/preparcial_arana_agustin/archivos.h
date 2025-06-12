#ifndef _ARCHIVOS_H
#define _ARCHIVOS_H

int inAbrirArchivo(char *, char *);
int inLeerArchivo(char *, char *);
int inEscribirArchivo(char *, char *);
int inLeerLineaPorLinea(char *, int);
int inCerrarArchivo();
long obtenerPosicionPuntero();
int inIrAPosicion(long);

#endif

/*
 * Obviamente, si no usa el framework, estas desaprobado
 * Pensar en otras funciones que consideremos utiles
 * */
