cmake_minimum_required(VERSION 3.29)
project(recuperatorio_2 C)

set(CMAKE_C_STANDARD 90)

add_executable(jugadores
        claves_ipc.h
        claves_ipc.c
        semaforos.h
        semaforos.c
        colas.h
        colas.c
        aleatorios.h
        aleatorios.c
        utils.h
        utils.c
        memoria.h
        memoria.c
        jugadores.c
        thread.c
        thread.h
        defs.h)

add_executable(panel
        defs.h
        claves_ipc.h
        claves_ipc.c
        semaforos.h
        semaforos.c
        colas.h
        colas.c
        aleatorios.h
        aleatorios.c
        utils.h
        utils.c
        memoria.h
        memoria.c
        cancha.c)
