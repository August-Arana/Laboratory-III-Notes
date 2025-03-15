#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "def.h"
#include "time.h"
#include "funciones.h"
#include "archivos.h"


int main (int arc ,char *argv[])
{
char szNombreArchivo[] = "productos.txt";
char produc [15+1];
char Producto[20+1];
int i=0;

  if (arc > 1) {  
        strncpy(produc,argv[1], sizeof(produc) - 1);  

        printf("El argumento es: %s\n", produc);
    } else {
        printf("No se proporcionaron argumentos.\n");
    }
convertirAMayusculas(produc);
inAbrirArchivo(szNombreArchivo,"w");
for ( i=1;i <= CANTIDAD; i++)
{
    sprintf(Producto, "%s-%02d\n",produc, i);  
    inEscribirArchivos(Producto);  
}

voCerrarArchivo();
inAbrirArchivo(szNombreArchivo, "r");
inLeerArchivos(szNombreArchivo);
voCerrarArchivo();

return 0;
}
