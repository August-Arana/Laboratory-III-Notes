#include "utils.h"

char *descripcion_operacion(int id_operacion) {
    switch (id_operacion) {
        case 0: return "Cheque";
        case 1: return "Efectivo";
        default: return "Desconocido";
    }
}
