#ifndef _ARCHIVO
#define _ARCHIVO

FILE *fiAbrirArchivo(char *nombreArchivo,char *modo);
void voCerrarArchivo(FILE *archivo);
int inLeerArchivo(FILE *archivo,void *buffer, int cantidad);
int inEscribirArchivo(FILE *archivo,void *buffer,int cantidad);
int inLeerLinea(FILE *archivo,char *buffer,int cantidad);
int inEscribirLinea(FILE *archivo,char *buffer);
int inRenombrarArchivo(char *nombreViejo,char *nombreNuevo);




#endif
