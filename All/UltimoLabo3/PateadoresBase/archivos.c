#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "archivos.h"
#include "def.h"
#include "funciones.h"

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

char* inLeerArchivo() {
   
    char buffer[256];
    size_t contenidoLength = 0;
	size_t bufferLength;
    size_t bufferSize = 1024;
	char *temp;
	char *contenido;

    contenido = (char*)malloc(bufferSize * sizeof(char)); 
    if (contenido == NULL) {
        return NULL; 
    }

    contenido[0] = '\0'; 


    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        bufferLength = strlen(buffer);
        
        if (contenidoLength + bufferLength >= bufferSize) {
            bufferSize *= 2; 
            temp = realloc(contenido, bufferSize * sizeof(char));
            if (temp == NULL) {
                free(contenido);
                return NULL; 
            }
            contenido = temp;
        }
        strcat(contenido, buffer);
        contenidoLength += bufferLength;
    }

    return contenido;
}
int inContarLineas(int contador){

	char buffer[1024];

	while(fgets(buffer,1024,fp)!=NULL){
		contador++;
	}

	return contador;
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
char* inLeerArchivoPrimeraLinea( int dimension)
{
   
    char *szTextoALeer = (char*) malloc(dimension * sizeof(char));
    
    if (szTextoALeer == NULL) 
    {
        return NULL;
    }

    
    if (fgets(szTextoALeer, dimension, fp) != NULL)
    {
        return szTextoALeer;  
    }

    free(szTextoALeer);
    return NULL;
}
int inEscribirArchivo( char *szTextoAEscribir){
   
		fprintf(fp, szTextoAEscribir);
		return TRUE;
	

}

int inContarAciertosLectura(char *palabraClave,int *contador){

	char buffer[200];

	while(!feof(fp)){
		fscanf(fp,"%s",buffer);
		if(strcmp(buffer,palabraClave)==0){
			(*contador)++;
		}
		memset(buffer,0,200);	
	}
	return TRUE;	
}

int inRenombrarArchivo(char *nombreViejo, char *nombreNuevo){

	return rename(nombreViejo,nombreNuevo);

}
