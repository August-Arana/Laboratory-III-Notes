#include "cola.h"
#include <stdio.h>
#include <unistd.h>

int main() {
    int id_cola = creo_id_cola_mensajes(1234);

    mensaje msg;

    printf("Proceso 2: esperando mensaje...\n");
    if (recibir_mensaje(id_cola, 2, &msg) == -1) {
        perror("Error al recibir mensaje");
    } else {
        printf("Proceso 2: mensaje recibido\n");
        printf("  De: %d\n", msg.int_rte);
        printf("  Evento: %d\n", msg.int_evento);
        printf("  Contenido: %s\n", msg.char_mensaje);
    }

    return 0;
}

