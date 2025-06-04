#include "definiciones.h"
#include "funciones.h"

int main() {
  int id_cola_mensajes;
  int saldos[100];
  int i;
  int cliente;
  int cant;
  char response_msg[100];

  for(i=0; i <100; i++){
    saldos[i]=0;
  }
	id_cola_mensajes 	= creo_id_cola_mensajes(CLAVE_BASE);
  mensaje msg;
  while(1) {
    printf("Espera mensaje\n");
    recibir_mensaje(id_cola_mensajes, MSG_VERIFICADOR, &msg);
    int count = 0;
    int n1;
    int n2;
    char *token;
    int result;
    printf("Mensaje %s\n",msg.char_mensaje);
    switch (msg.int_evento)
    {
      case EVT_VERIFICAR:
        printf("Verificando ...\n");
        token = strtok(msg.char_mensaje, "|");
        while (token != NULL)
        {
          switch (count)
          {  
            case 0:
              n1 = atoi(token); 
            break;
            case 1:
              n2 = atoi(token);
            break;
          } 
          token = strtok(NULL,"|");
          count++;
        } 
        printf("Procesando numeros: %i %i\n",n1,n2); 
        if(n1 == n2) {
          printf("Emitiendo EVT_IGUALES\n");
          enviar_mensaje(id_cola_mensajes,msg.int_rte,MSG_VERIFICADOR, EVT_IGUALES, ""); 
        } else {
          printf("Emitiendo EVT_DISTINTOS\n");
          enviar_mensaje(id_cola_mensajes,msg.int_rte,MSG_VERIFICADOR, EVT_DISTINTOS, ""); 
        }
  
        break;
      default:
        printf("\nEvento sin definir\n");
      break;
    }
  }  
}

