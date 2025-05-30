#ifndef _GLO_
#define _GLO_
#include <pthread.h>
/* En este archivo, Declaracion de variables o de estructura, nada mas
Fijate que en global.h haces, lo que decias antes, de exponer las variables que van a ser usadas por el resto del codigo.
 Nunca inicializo valores globales en estos archivos
*/

extern char chValGlob;
extern int inNumGlob;
extern int CLAVE_BASE;
extern int global_counter;
extern int g_carton_lleno;
extern int g_control;
extern int bolilla;
extern pthread_mutex_t mutex;
#endif
