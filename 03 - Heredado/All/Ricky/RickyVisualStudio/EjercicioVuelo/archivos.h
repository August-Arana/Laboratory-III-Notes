#ifndef _ARCHVOS
#define _ARCHIVOS

int inAbrirArchivo(char *szNombreArchivo, char *szTipoAp);
void voCerrarArchivo();
int inLeerArchivoPorLinea(char *szTextoALeer);
int inLeerArchivos(char *szNombreArchivo);
int inEscribirArchivos(char *szTextoAEscribir);
int inRenombrarArchivo(char *nombreViejo,char *nombreNuevo);
int inContarAciertosLectura(char *palabraClave,int contador);

#endif 
