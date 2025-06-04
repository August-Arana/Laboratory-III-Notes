#ifndef _DEFINICIONES_H
#define _DEFINICIONES_H

#define CANTIDAD_MAX_CAJEROS 10
 
typedef struct tipo_destinatarios destinatarios;
struct tipo_destinatarios
{
	int destino;
	int libre;
};


typedef enum
{
	MSG_NADIE,				
	MSG_VERIFICADOR,		
	MSG_SOLICITANTE,			
}Destinos;

typedef enum
{
  EVT_VERIFICAR,
  EVT_IGUALES,
  EVT_DISTINTOS
}Eventos;


#endif
