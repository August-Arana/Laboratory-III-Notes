#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "def.h"

FILE *fp;
int abierto;

int inAbrirArchivo(char *szNombreArchivo, char *szModo)
{	

	fp = fopen(szNombreArchivo,szModo);
	if(fp==NULL)
		return FALSE;
	else
		return TRUE;
}

void voCerrarArchivo()
{

	fclose(fp);
}

int inLeerArchivo(char *szNombreArchivo)
{
	abierto=inAbrirArchivo(szNombreArchivo,"r");
	
	if(abierto==1){

		char buffer[255];
	
	
		while(fgets(buffer,sizeof(buffer),fp) != NULL){
			printf("%s",buffer);
		}

		voCerrarArchivo(fp);
		return TRUE;
	}
	else{
		printf("error\n");
		return FALSE;
	}

}

int inLeerArchivoPorLinea(char *szNombreArchivo,char *szTextoALeer){
	abierto=inAbrirArchivo(szNombreArchivo,"r");

	if(abierto==1){	
		while(!feof(fp))
		{	
			fscanf(fp,"%s",szTextoALeer);	
			printf("%s\n",szTextoALeer);

		}
	}else{
		printf("error\n");
		return FALSE;
	}

	return TRUE;
}


int inEscribirArchivo(char *szNombreArchivo,char *szTextoAEscribir)
{	
	abierto=inAbrirArchivo(szNombreArchivo,"w");

	if(abierto==1){	
		fprintf(fp,szTextoAEscribir);
		voCerrarArchivo();
		return TRUE;
	}else{
		printf("error\n");
		return FALSE;
	}
	return FALSE;

}

int inEscribirArchivoPorLinea(char *szNombreArchivo,char *szTextoAEscribir)
{
	abierto=inAbrirArchivo(szNombreArchivo,"a");

	if(abierto==1){	
		fprintf(fp,szTextoAEscribir);
		/*printf("archivo escrito\n");*/
		voCerrarArchivo();
		return TRUE;
	}else{
		printf("error\n");
		return FALSE;
	}
}


int inLeerArchivoBusqueda(char *szNombreArchivo, char *szPalabraClave, int *contador){
	char szBuffer[LARGO];
	
	abierto=inAbrirArchivo(szNombreArchivo,"r");
	if(abierto==1){
		while(!feof(fp)){
			fscanf(fp,"%s",szBuffer);
			if(strcmp(szBuffer,szPalabraClave)==0){
				(*contador)++;
			}	
			strcpy(szBuffer,"");	
		}
		
	}
	else{		
		return FALSE;
	}	
	return TRUE;
}


int inObtenerValor(char *szNombreArchivo, char *szPalabraClave, int *contador){
	char buffer[LARGO];

	abierto=inAbrirArchivo(szNombreArchivo,"r");
	if(abierto==1){
		while(!feof(fp)){
			fscanf(fp,"%s",buffer);
			if(strcmp(buffer,szPalabraClave)==0){
				fscanf(fp,"%s",buffer);
				
				(*contador) += atoi(buffer);
							
			}		
		}
		return TRUE;
	}
	else{
		printf("no se abrio\n");		
		return FALSE;
	}	
	return TRUE;
}
















