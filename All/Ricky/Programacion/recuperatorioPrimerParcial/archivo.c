#include "stdio.h"
#include "archivo.h"
#include "string.h"



FILE *fiAbrirArchivo(char *nombreArchivo, char *modo){

	FILE *archivo = fopen(nombreArchivo,modo);
	return archivo;
}

void voCerrarArchivo(FILE *archivo){
	
	fclose((FILE *)archivo);

}

int inContarAciertosLectura(FILE *archivo,char *palabraClave,int contador){

	char buffer[1024];

	while(!feof(archivo)){
		fscanf(archivo,"%s",buffer);
		if(strcmp(buffer,palabraClave)==0){
			contador++;
		}
		memset(buffer,0,1024);	
	}
	return contador;	
}

int inContarLineas(FILE *archivo,int contador){

	char buffer[1024];

	while(fgets(buffer,1024,archivo)!=NULL){
		contador++;
	}

	return contador;

}

char *chBuscarPalabraClave(FILE *archivo,char *palabraClave){

	char Buffer[1024];

	while(!feof(archivo)){
		fscanf(archivo,"%s",Buffer);
		if(strcmp(Buffer,palabraClave)==0){
			strcpy(palabraClave,Buffer);
		}
		memset(Buffer,0,1024);	
	}
	return palabraClave;

}

int inLeerLinea(FILE *archivo,char *buffer,int cantidad){

	
		if(fgets(buffer,cantidad,archivo) != NULL)
		{
			printf("Lectura exitosa\n");
			return 0;
		}else{
			printf("Error en lectura\n");
			return 1;
		}
	
	}
	


int inEscribirLinea(FILE *archivo,char *buffer){

	return fprintf(archivo,"%s\n",buffer);

}

int inRenombrarArchivo(char *nombreViejo, char *nombreNuevo){

	return rename(nombreViejo,nombreNuevo);

}

