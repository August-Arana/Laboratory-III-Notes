#ifndef _MEMORIA
#define _MEMORIA


void *creoMemoria(int size,int *r_id_memoria, int clave_base);
void voLiberar_memoria(void* ptr_memoria, int id_memoria);


#endif
