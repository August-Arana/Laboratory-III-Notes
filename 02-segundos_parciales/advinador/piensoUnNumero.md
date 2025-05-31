# Examen Segundo Parcial

## Consignas

### Pienso un número

Se trata de un proceso PIENSO y otro JUGADOR.
Utiliza cola de mensajes con los siguientes IDs:

    MSG_NADIE 0
    MSG_PIENSO 1
    MSG_JUGADOR 2
    EVT_NINGUNO 0
    EVT_NUMERO 1 // Lleva como parámetro un número de 1 al 99
    EVT_ACERTO 2
    EVT_NO_ACERTO 3
    EVT_FINALIZAR 4

#### Proceso PIENSO (MSG_PIENSO)

1. “Piensa un número” genera en forma aleatoria un número del 1 al 99 y lo guarda en una variable local int pienso_un_numero;
2. Borrar los mensajes anteriores, para empezar de 0.
3. Espera recibir EVT_NUMERO del jugador, compara el número recibido con pienso_un_numero.
   1. En caso de acierto, le envía un EVT_ACERTO al jugador.
   2. En caso de no acierto, responde con un EVT_NO_ACERTO al jugador.
4. En caso de no haber aciertos, sigue con el punto 3.
5. Si hubo acierto, muestra por pantalla el número del jugador ganador y finaliza.

#### Proceso JUGADOR

##### HiloMain:

- Solicita por teclado la cantidad de jugadores.
- Lanza tantos hilos como jugadores ingresados.
- Espera que finalicen los hilos.

##### HiloJugador:

1. Genera un número al azar de 1 al 99 (no repetitivos).
2. Envía EVT_NUMERO a MSG_PIENSO con el número que generó en el punto 1.
3. Espera recibir un evento del proceso PIENSO:
   - Si recibe un mensaje EVT_ACERTO, muestra la cantidad de intentos y envía un EVT_FINALIZAR a todos los jugadores, incluido el mismo.
   - Si recibe un mensaje EVT_NO_ACERTO, sigue con el punto 1.
   - Si recibe un mensaje EVT_FINALIZAR, finaliza el hilo.
