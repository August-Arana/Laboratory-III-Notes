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

int inLeerArchivo(FILE *archivo,void *buffer,int cantidad){

	return fread(buffer,1,cantidad,(FILE *)archivo);

}

int inEscribirArchivo(FILE *archivo,void *buffer, int cantidad){

	return fwrite(buffer, 1, cantidad,(FILE *)archivo);

}

int inLeerLinea(FILE *archivo,char *buffer,int cantidad){

	size_t longitud;
		if(fgets(buffer,cantidad,archivo) != NULL){
			longitud = strlen(buffer);
				if(longitud > 0 && buffer[longitud -1] == '\n'){
					buffer[longitud -1] = '\0';
					return 1;
				}
	
	}
	return 0;
}

int inEscribirLinea(FILE *archivo,char *buffer){

	return fprintf(archivo,"%s\n",buffer);

}

int inRenombrarArchivo(char *nombreViejo, char *nombreNuevo){

	return rename(nombreViejo,nombreNuevo);

}
