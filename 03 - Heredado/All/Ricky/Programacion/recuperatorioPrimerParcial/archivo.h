#ifndef _ARCHIVO
#define _ARCHIVO

FILE *fiAbrirArchivo(char *nombreArchivo,char *modo);
void voCerrarArchivo(FILE *archivo);
int inContarAciertosLectura(FILE *archivo,char *palabraClave, int contador);
int inContarLineas(FILE *archivo,int contador);
char *chBuscarPalabraClave(FILE *archivo,char *palabraClave);
int inLeerLinea(FILE *archivo,char *buffer,int cantidad);
int inEscribirLinea(FILE *archivo,char *buffer);
int inRenombrarArchivo(char *nombreViejo,char *nombreNuevo);





#endif
