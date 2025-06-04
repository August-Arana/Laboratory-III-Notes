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

int inLeerArchivo(char *szNombreArchivo){
   

		char buffer[255];

		while (fgets(buffer, sizeof(buffer), fp) != NULL)
		{
			printf("%s", buffer);
		}

		
		return TRUE;
	

}

int inLeerArchivoPorLinea( char *szTextoALeer)
{
	
		while (!feof(fp))
		{
			fscanf(fp, "%s", szTextoALeer);
			printf("%s\n", szTextoALeer);
		}
	

	  return TRUE;
}

int inEscribirArchivo( char *szTextoAEscribir){
   
		fprintf(fp, szTextoAEscribir);
		return TRUE;
	

}

int inContarAciertosLectura(char *palabraClave,int contador){

	char buffer[1024];

	while(!feof(fp)){
		fscanf(fp,"%s",buffer);
		if(strcmp(buffer,palabraClave)==0){
			contador++;
		}
		memset(buffer,0,1024);	
	}
	return contador;	
}

int inRenombrarArchivo(char *nombreViejo, char *nombreNuevo){

	return rename(nombreViejo,nombreNuevo);

}
