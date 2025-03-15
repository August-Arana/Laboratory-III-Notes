#ifndef _ARCHIVOS
#define _ARCHIVOS

int inAbrirArchivo(char *szNombreArchivo, char *szTipoAp);
void voCerrarArchivo(void);
int inLeerArchivoPorLinea(char *szTextoALeer);
char* inLeerArchivo(void);
int inContarLineas(int contador);
int inEscribirArchivo(char *szTextoAEscribir);
int inRenombrarArchivo(char *nombreViejo,char *nombreNuevo);
int inContarAciertosLectura(char *palabraClave,int *contador);

#endif 
