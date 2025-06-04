#include <stdio.h>

int preguntar_si_no(char *mensaje)
{
    char respuesta[100];
    printf("%s (s/n): ", mensaje);
    scanf("%s", respuesta);
    return (respuesta[0] == 's' || respuesta[0] == 'S');
}
