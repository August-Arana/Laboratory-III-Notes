Ejercicio 2: Bolos
 
Se trata de un proceso BOLERA y otro JUGADORES con varios hilos (uno por cada jugador).
Utiliza cola de mensajes con los siguientes IDs:

 
Proceso BOLERA (MSG_ BOLERA)
Hilo Principal (main):
1) La cantidad de jugadores es siempre 2.
2) Borrar los mensajes anteriores, para empezar de 0. listo
3. Inicializa una vector local de dos posiciones, uno por cada línea de bolos que le corresponde a cada jugador. Ambas posiciones se inicializan con la cantidad de 10 pinos. listo

4) Le envía un mensaje a cada JUGADOR, EVT_INICIO. (MSG_JUGADOR+i). listo

5) Espera recibir mensajes de los JUGADORES.

Si recibe EVT_TIRO.
    • Define al azar los pinos tirados del 1 hasta la cantidad de pinos disponibles (cuidado: utilizar la línea correcta dependiendo del jugador)
    • Actualiza el vector con la posición correcta con la cantidad de pinos en pie.
    • Si se tiran todos los pinos de una vez, muestra la leyenda “CHUZA”.
    • Devuelve la cantidad de pinos tirados al jugador con el EVT_RESULTADO, cantidad_de_pinos.
    • Si se tiran todos los pinos o ya recibió 3 tiros de ese jugador, envía el EVT_FIN al jugador correspondiente (esto lo hace en lugar de EVT_RESULTADO) con la cantidad de puntos obtenidos (1 por cada pino tirado y 20 si se tiran todos de una).
6) Si terminaron de tirar los 2 jugadores (o bien tiraron todos los pinos o tiran 3 veces), finaliza.
7) Caso contrario, repite desde el punto 5.
 
Proceso JUGADORES 
El hilo principal (main): 
    • La cantidad de jugadores es siempre 2.
    • Lanza tantos HiloJUGADOR como JUGADORES haya.
    • Se queda esperando que terminen los hilos.
    • Muestra el puntaje de cada jugador e indica quién ganó por pantalla (recibido de los hilos).
 
HiloJUGADOR (uno por JUGADOR): (MSG_JUGADOR+nro_JUGADOR)
1) Espera recibir el EVT_INICIO. listo
2) Escribir por pantalla, “Soy el jugador N y voy a tirar“.listo
3) Envía al BOLERA el EVT_TIRO.
4) Espera recibir el EVT_RESULTADO o EVT_FIN. listo
5) Muestra por pantalla los bolos tirados “Soy el jugador N y tire X bolos”.
6) Espera 300 ms y vuelve a tirar.
7) Se recibe el EVT_FIN; termina el hilo devolviendo los puntos obtenidos. 
8) Muestra por pantalla los puntos obtenidos.
 
Utilizar Makefile con la estructura de archivos vista en la cursada.
 
