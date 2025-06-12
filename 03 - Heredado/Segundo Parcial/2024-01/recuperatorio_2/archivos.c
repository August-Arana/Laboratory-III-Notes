#include <stdio.h>
#include "archivos.h"

#include <string.h>
#include <unistd.h>

#include "defs.h"

FILE *abrir_archivo(char *nombreArchivo, char *modo) {
    FILE *archivo = fopen(nombreArchivo, modo);
    return archivo;
}

int eliminar_archivo(char *nombreArchivo) {
    return remove(nombreArchivo);
}

void cerrar_archivo(FILE *fd) {
    fclose((FILE *)fd);
}

int leer_archivo(FILE *fd, void *buffer, int cantidad) {
    return fread(buffer, 1, cantidad, (FILE *)fd);
}

int escribir_archivo(FILE *fd, void *buffer, int cantidad){
    int written;
    written = fwrite(buffer, 1, cantidad, (FILE *)fd);
    fflush(fd);
    return written;
}

void posicionar_archivo_al_principio(FILE *fd) {
    fseek(fd, 0, SEEK_SET);
}

void posicionar_archivo_al_final(FILE *fd) {
    fseek(fd, 0, SEEK_END);
}

int leer_linea(FILE *fd, char *buffer, int cantidad) {
    size_t longitud;
    if (fgets(buffer, cantidad, fd) != NULL) {
        longitud = strlen(buffer);
        if (longitud > 0 && buffer[longitud - 1] == '\n') {
            buffer[longitud - 1] = '\0';
            return 1;
        }
    }
    return 0;
}

int escribir_linea(FILE *fd, char *buffer) {
    int written;
    written = fprintf(fd, "%s\n", buffer);
    fflush(fd);
    return written;
}

int renombrar_archivo(char *nombreViejo, char *nombreNuevo) {
    return rename(nombreViejo, nombreNuevo);
}
