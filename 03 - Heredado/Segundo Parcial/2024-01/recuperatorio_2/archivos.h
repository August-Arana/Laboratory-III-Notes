#ifndef _ARCHIVOS_H
#define _ARCHIVOS_H

/**
 * Abre un archivo
 * @param nombreArchivo nombre del archivo
 * @param modo modo de apertura del archivo
 * @return file descriptor
 */
FILE *abrir_archivo(char *nombreArchivo, char *modo);

/**
 * Elimina un archivo
 * @param nombreArchivo nombre del archivo a eliminar
 * @return int 0 si se elimino correctamente, -1 si no
 */
int eliminar_archivo(char *nombreArchivo);

/**
 * Cierra un archivo
 * @param fd file descriptor
 */
void cerrar_archivo(FILE *fd);

/**
 * Lee un archivo
 * @param fd file descriptor
 * @param buffer buffer a guardar la informacion que se lee
 * @param cantidad cantidad de bytes a leer
 * @return cantidad de bytes que se leyeron
 */
int leer_archivo(FILE *fd, void *buffer, int cantidad);

/**
 * Escribe un archivo
 * @param fd file descriptor
 * @param buffer buffer a escribir en el archivo
 * @param cantidad cantidad de bytes a escribir
 * @return cantidad de bytes que se escribieron
 */
int escribir_archivo(FILE *fd, void *buffer, int cantidad);

/**
 * Posiciona al principio de un archivo
 * @param fd file descriptor
  */
void posicionar_archivo_al_principio(FILE *fd);

/**
 * Posiciona el archivo al final
 * @param fd file descriptor
 */
void posicionar_archivo_al_final(FILE *fd);

/**
 * Lee una linea de un archivo
 * @param fd file descriptor
 * @param buffer buffer a guardar la linea que se lee
 * @param cantidad cantidad de bytes a leer
 * @return cantidad de bytes que se leyeron
 */
int leer_linea(FILE *fd, char *buffer, int cantidad);

/**
 * Escribe una linea en un archivo
 * @param fd  file descriptor
 * @param buffer buffer a escribir
 * @return cantidad de bytes que se escribieron
 */
int escribir_linea(FILE *fd, char *buffer);

/**
 * Renombra un archivo
 * @param nombreViejo nombre del archivo a renombrar
 * @param nombreNuevo nuevo nombre del archivo
 * @return 0 si se renombro correctamente, -1 si no
 */
int renombrar_archivo(char *nombreViejo, char *nombreNuevo);

#endif
