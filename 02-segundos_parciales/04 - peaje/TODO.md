Proceso PEAJE:
Recibe por parámetro la cantidad de vías.
El hilo principal (main):
Lanza tantos ThreadVia como vías se haya ingresado por parámetro. Listo
Se queda esperando que terminen los threads. Listo
Al finalizar los threads se debe sumar la cantidad de liberaciones de todas las vías, (recibir la cantidad de cada thread y sumar). Mostrar el total por pantalla.
 
ThreadVia (uno por vía):
    1. Cada ThreadVia lleva una variable la cantidad_vehiculos_en_cola (inicializada en 0). Y realiza lo siguiente:
    2. Espera recibir un mensaje MSG_VIA (+el número de vía)
    3. Cada vez que recibe un EVT_VEHICULOS, suma la cantidad recibida a cantidad_vehiculos_en_cola
    4. Descuenta de cantidad_vehiculos_en_cola (siempre que haya vehículos) N vehículos (N aleatorio de 1 a 10) de su cola de vehículos.
    5. Si detecta que tiene más de 10 vehículos en cola debe liberar la vía poniendo la cantidad en 0, contando la cantidad de liberaciones.
    6. Mostrar por pantalla la cantidad de vehículos que tiene en cola.


Proceso AUTOS
Recibe por parámetro la cantidad de vías (igual que PEAJE) y la cantidad de vehículos a generar (por ejemplo 500 vehículos): Listo
    1. A continuación va generando vehículos en forma aleatoria de 1 a 5. Listo
    2. Selecciona una vía en forma aleatoria. Listo
    3. Utiliza el EVT_VEHICULOS para enviar el mensaje a la vía (MSG_VIA + nro vía) con la cantidad de vehículos a acolar (los del punto 1). Listo
    4. Se descuentan estos vehículos (los del punto 1) de los vehículos a generar. Listo
    5. Si se llegó a la cantidad de vehículos a generar, envía EVT_FINALIZA a todas las vías y TERMINA. Listo
    6. Si no, espera N ms (N aleatorio entre 100 y 500ms) y repite desde el punto 1. Listo
