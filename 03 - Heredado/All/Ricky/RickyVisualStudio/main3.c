#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "def.h"
#include "time.h"
#include "funciones.h"
#include "archivos.h"

int main(int arc ,char *argv[])
{
    
    const char *szMensaje=("Mi mensaje");
    char szMensaje2[20+1];
    int inDat=0;
    int n=0;
    int x=0;

    char szVar(10+1);
    char *szVarDina;
    int inEntero[3];
    int *inEnteroDina;


    szVarDina=(char*)malloc(sizeof(char)*11);
    inEnteroDina=(int*)malloc(sizeof(int)*3);

    inEntero[0]=15
    *inEnteroDina=20;
    memset(szVar,0x00,sizeof(szVar));
    memset(szVarDina,0x00,sizeof(szVarDina));
    szVar[0]=0x02;
    szVarDina[0]="C";




    srand(time(0));



    for(n=1;n<=CANTIDAD;n++){
       inDat=inDevolverNumeroAleatorio(DESDE,HASTA);
        printf("Valor %i %i\n",n,inDat);
    }
    printf("hola Up\n");

    printf("cant arg: %i %s %s\n",arc,argv[0],argv[1]);
    printf("Mensaje1: %s\n",szMensaje);
    if(arc==2){


        inDat=atoi(argv[1]);
        if(inDat==TRUE){
            printf("SI\n");
        }

    }

    memset(szMensaje2,0x20,sizeof(szMensaje2));
    memcpy(&szMensaje2[0],"Juan",4);

    while(x<30)
    {

        printf("%c %02x \n",szMensaje2[x],szMensaje2[x]);
        printf("pase %d \n", x);

        x++;
    }


    printf("Mensaje2: %s",szMensaje2);
    
    return 0;
}
