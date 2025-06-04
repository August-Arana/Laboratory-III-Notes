#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "ctype.h"
#include "funciones.h"
#include "errno.h" 
#include "limits.h"



int inDevolverNumeroAleatorio(int inDesde,int inHasta)
{


    int inValorAleatorio=0;
    inValorAleatorio=rand()%(inHasta-inDesde+1)+inDesde;

    return inValorAleatorio;


}

void convertirAMayusculas(char *cadena) {
    while (*cadena) {
        *cadena = toupper((unsigned char) *cadena);
        cadena++;
    }
}

void filtrarContenidoPorClave(const char *mensaje, const char *clave, char *resultado) {
    char *posClave;
    const char *inicio;
    const char *fin;
    int longitud;

    posClave = strstr(mensaje, clave);
    if (posClave) {
        inicio = strchr(posClave, ':');
        if (inicio) {
            inicio++;
            fin = strpbrk(inicio, ",.");
            if (fin) {
                longitud = fin - inicio;
                if (longitud >= 100) { 
                    longitud = 99;
                }
                strncpy(resultado, inicio, longitud);
                resultado[longitud] = '\0';
            } else {
                strncpy(resultado, inicio, 99);
                resultado[99] = '\0';
            }
        } else {
            resultado[0] = '\0';
        }
    } else {
        resultado[0] = '\0';
    }
}

void filtrarContenidoPorClaveAEntero(const char *mensaje, const char *clave, int *resultado) {
    char *posClave;
    const char *inicio;
    const char *fin;
    char buffer[100];
    int longitud;

    posClave = strstr(mensaje, clave);
    if (posClave) {
        inicio = strchr(posClave, ':');
        if (inicio) {
            inicio++;
            fin = strpbrk(inicio, ",.");
            if (fin) {
                longitud = fin - inicio;
                if (longitud >= 100) {
                    longitud = 99;
                }
                strncpy(buffer, inicio, longitud);
                buffer[longitud] = '\0';
            } else {
                strncpy(buffer, inicio, 99);
                buffer[99] = '\0';
            }
            *resultado = atoi(buffer);
        } else {
            *resultado = 0;
        }
    } else {
        *resultado = 0;
    }
}
