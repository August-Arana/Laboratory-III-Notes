#include <stdio.h>

int preguntar_si_no(char *mensaje)
{
    char respuesta[100];
    printf("%s (s/n): ", mensaje);
    scanf("%s", respuesta);
    return (respuesta[0] == 's' || respuesta[0] == 'S');
}

int consultar_opcion(char *mensaje, int cantidad_opciones)
{
    int respuesta;
    while (1)
    {
        printf("\n%s", mensaje);
        scanf("%d", &respuesta);
        if (respuesta > 0 && respuesta <= cantidad_opciones)
            return respuesta;
        else
            printf("Opcion invalida\n");
    }
}
