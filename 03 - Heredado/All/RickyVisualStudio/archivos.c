#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "archivos.h"
#include "def.h"

FILE *fp;


int inAbrirArchivo(char *sznombre, char *szTipoAp){
    fp=fopen(sznombre,szTipoAp);
    if(fp==NULL){
        printf("Error al abrir archivo\n");
        return FALSE;
    }

    return TRUE;
}

void voCerrarArchivo(){

    fclose(fp);  

}

int inLeerArchivos(char *szNombreArchivo){
   

		char buffer[255];

		while (fgets(buffer, sizeof(buffer), fp) != NULL)
		{
			printf("%s", buffer);
		}

		
		return TRUE;
	

}

int inEscribirArchivos( char *szTextoAEscribir){
   
		fprintf(fp, szTextoAEscribir);
		return TRUE;
	

}
