#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CANTIDAD 10

pthread_mutex_t mutex;

typedef struct tipo_ejec operacion;
struct tipo_ejec
{
	int n1;
	int n2;
  int result;
};

void *funcionThreadSuma (void *parametro)
{
  operacion *ex = (operacion*) parametro;
  int n;
  ex->result = ex->n1 + ex->n2;

  pthread_exit ((void *)"Listo");
}
void *funcionThreadProducto (void *parametro)
{
  operacion *ex = (operacion*) parametro;
  int n;
  ex->result = ex->n1 * ex->n2;

  pthread_exit ((void *)"Listo");
}
int main(int argc, char * argv[])
{
 
  int n1;
  int n2;
  n1 = atoi(argv[1]); 
  n2 = atoi(argv[2]);
  operacion* suma = (operacion*) malloc(sizeof(operacion)*1);
  operacion* producto = (operacion*) malloc(sizeof(operacion)*1);
  suma->n1 = n1;
  suma->n2 = n2;
  producto->n1 = n1;
  producto->n2 = n2;

  pthread_t     idHiloSuma;
  pthread_t     idHiloProducto;
  pthread_attr_t  atributos;
  
  pthread_attr_init (&atributos);
  pthread_attr_setdetachstate (&atributos, PTHREAD_CREATE_JOINABLE);
  printf("Lanzando hilo de suma\n");
  if (pthread_create (&idHiloSuma, &atributos, funcionThreadSuma, (void*)suma)!= 0)
  {
    perror ("No puedo crear thread suma");
    exit (-1);
  }
  
  printf("Lanzando hilo de producto\n");
  if (pthread_create (&idHiloProducto, &atributos, funcionThreadProducto, (void*)producto)!= 0)
  {
    perror ("No puedo crear thread producto");
    exit (-1);
  }
  printf("Esperando Hilos\n");
  pthread_join (idHiloSuma, NULL); 
  pthread_join (idHiloProducto, NULL); 
  printf("Resultado Suma: %i\n", suma->result); 
  printf("Resultado Producto: %i\n", producto->result); 
   
  return 0;
}
