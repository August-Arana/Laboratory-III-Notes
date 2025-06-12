#include "aleatorios.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void inicializar_semilla_random(void) {
    srand(time(0));
}

int generar_int(void) {
    return rand();
}

int generar_int_acotado(int from, int to) {
    return (rand() % (to - from + 1)) + from;
}

int verificar_numero_en_vector(s_numero *vector, int numero) {
    int i;

    for (i = 0; i < sizeof(vector); i++) {
        if (vector[i].numero == numero) {
            return 1;
        }
    }

    return 0;
}

s_numero *generar_vector_aleatorio(int cantidad) {
    int i, nuevo_numero;
    s_numero *vector = (s_numero *)malloc(cantidad * sizeof(s_numero));
    memset(vector, 0, cantidad * sizeof(s_numero));
    for (i = 0; i < cantidad; i++) {
        do {
            nuevo_numero = generar_int();
        } while (verificar_numero_en_vector(vector, nuevo_numero));
        vector[i].numero = nuevo_numero;
    }
    return vector;
}

s_numero *generar_vector_aleatorio_acotado(int cantidad, int from, int to) {
    int i, nuevo_numero;
    s_numero *vector = (s_numero *)malloc(cantidad * sizeof(s_numero));
    memset(vector, 0, cantidad * sizeof(s_numero));
    for (i = 0; i < cantidad; i++) {
        do {
            nuevo_numero = generar_int_acotado(from, to);
        } while (verificar_numero_en_vector(vector, nuevo_numero));
        vector[i].numero = nuevo_numero;
    }
    return vector;
}

void generar_nombre_aleatorio(char *nombre) {
    int idx = rand() % 50;
    char* nombres[50] = {
        "Luis", "Sofia", "Juan", "Valentina", "Carlos",
        "Camila", "Pedro", "Mariana", "Mateo", "Isabella",
        "Diego", "Daniela", "Javier", "Gabriela", "Alejandro",
        "Valeria", "Jorge", "Laura", "Andres", "Antonella",
        "Emilio", "Luciana", "Fernando", "Victoria", "Gustavo",
        "Renata", "Ricardo", "Ana", "Arturo", "Isabel",
        "Roberto", "Natalia", "Eduardo", "Paula", "Miguel",
        "Estefania", "Jose", "Juliana", "Francisco", "Marcela",
        "Manuel", "Catalina", "Luisa", "Rafael", "Maria",
        "Gonzalo", "Julia", "Oscar", "Elena", "Pablo"
    };

    strcpy(nombre, nombres[idx]);
}

void generar_apellido_aleatorio(char *apellido) {
    int idx = rand() % 50;
    char* apellidos[50] = {
        "García", "Fernández", "López", "Martínez", "González",
        "Rodríguez", "Pérez", "Sánchez", "Ramírez", "Torres",
        "Flores", "Vázquez", "Gómez", "Díaz", "Hernández",
        "Muñoz", "Jiménez", "Ruiz", "Álvarez", "Moreno",
        "Alonso", "Romero", "Gutiérrez", "Navarro", "Torres",
        "Cruz", "Morales", "Ortega", "Serrano", "Delgado",
        "Soto", "Castro", "Iglesias", "Ortiz", "Rubio",
        "Núñez", "Garrido", "Reyes", "Molina", "Santos",
        "Blanco", "Castillo", "Lozano", "Santiago", "Domínguez",
        "González", "Cabrera", "Marín", "Vega", "Méndez"
    };

    strcpy(apellido, apellidos[idx]);
}

void generar_nombre_y_apellido_aleatorio(char *nombre_y_apellido) {
    char nombre[20];
    char apellido[20];

    generar_nombre_aleatorio(nombre);
    generar_apellido_aleatorio(apellido);

    sprintf(nombre_y_apellido, "%s %s", nombre, apellido);
}

void generar_ciudad_aleatoria(char *ciudad) {
    int idx = rand() % 50;
    char* ciudades[50] = {
        "Buenos Aires", "Córdoba", "Rosario", "Mendoza", "La Plata",
        "Mar del Plata", "Salta", "Santa Fe", "San Juan", "Resistencia",
        "Corrientes", "Posadas", "Tucumán", "Neuquén", "Santiago del Estero",
        "Jujuy", "Bahía Blanca", "Paraná", "Formosa", "San Salvador de Jujuy",
        "San Miguel de Tucumán", "San Fernando del Valle de Catamarca", "La Rioja", "San Luis", "Río Gallegos",
        "Ushuaia", "Viedma", "Santa Rosa", "Rawson", "Corrientes",
        "Córdoba", "Paraná", "Formosa", "San Salvador de Jujuy", "La Rioja",
        "Mendoza", "Posadas", "Neuquén", "Viedma", "Salta",
        "San Juan", "San Luis", "Río Gallegos", "Santa Fe", "Santiago del Estero",
        "Ushuaia", "San Miguel de Tucumán", "San Fernando del Valle de Catamarca", "Santa Rosa", "Rawson"
    };

    strcpy(ciudad, ciudades[idx]);
}
