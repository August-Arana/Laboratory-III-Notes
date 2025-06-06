/* En este archivo, Declaracion de variables o de estructura, nada mas */
#include "global.h"

char chValGlob;
int inNumGlob;
int CLAVE_BASE;
/* no se suele inicializar aca, no lo deberias hacer aca, cambiar para despues*/
int global_counter = 0;
int g_carton_lleno = 0;
int g_control = 0;
int bolilla;
pthread_mutex_t mutex;

/* Nunca inicializo valores globales en estos archivos */
/* se puede? depende del codigo, pero en general, inicializar en el main, cuando las necesitas */
