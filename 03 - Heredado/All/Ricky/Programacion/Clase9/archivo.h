#ifndef _ARCHIVO
#define _ARCHIVO

int inAbrirArchivo(char *nombre, char *tipo);
void inCerrarArchivo();
void inLeerArchivo();
void inLeerArchivoBusqueda(char *szTextoALeer);
int inLeerArchivoBusquedaPorInt(char *szTextoALeer);
void inEscribirArchivo(char *texto);

#endif
