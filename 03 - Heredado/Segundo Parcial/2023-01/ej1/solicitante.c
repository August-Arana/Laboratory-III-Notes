#include "definiciones.h"
#include "funciones.h"
#include <sys/types.h>
#include <unistd.h>

void procesa_vuelta(int cola) {
  mensaje msg;
  recibir_mensaje(cola, MSG_SOLICITANTE, &msg);
  switch (msg.int_evento)
	{
    case EVT_IGUALES:
      printf("Los numeros ingresados fueron verificados como IGUALES\n");
    break;
    case EVT_DISTINTOS:
      printf("Los numeros ingresados fueron verificados como DISTINTOS\n");
    break;
    default:
			printf("\nEvento sin definir\n");
		break;
	}
}

int main() {

	int id_cola_mensajes;
	id_cola_mensajes 	= creo_id_cola_mensajes(CLAVE_BASE);
  while(1 == 1) {
    int n1;
    int n2;
    char cadena[100];
    printf("Ingrese dos numeros a verificar\n");
    printf("Numero 1: ");
    scanf("%i",&n1);
    printf("\nNumero 2: ");
    scanf("%i",&n2);
    printf("\n"); 
    sprintf(cadena, "%i|%i",n1,n2);
    enviar_mensaje(id_cola_mensajes , MSG_VERIFICADOR, MSG_SOLICITANTE, EVT_VERIFICAR, cadena);
    printf("\n********************************************************************************\n");
    procesa_vuelta(id_cola_mensajes);
    printf("********************************************************************************\n");
  }
}
