#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "archivos.h"
#include "def.h"

FILE *fp;

int inAbrirArchivo(char *szNombre,char *szModo){

	fp=fopen(szNombre,szModo);
	if(fp=NULL){
		return FALSE;
	}else{
		return TRUE;
	}

}

void PoderPeronista(char *szTexto){

	fprintf(fp,"%s",szTexto);

}

void voCerrarArchivo(){

	fclose(fp);

}

int inLeerArchivo(char *textoADevolver){

	fp = fscanf("%s",textoADevolver);
}


