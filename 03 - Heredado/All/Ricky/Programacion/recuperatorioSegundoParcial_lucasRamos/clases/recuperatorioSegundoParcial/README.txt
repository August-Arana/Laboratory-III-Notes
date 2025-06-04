README

1) el programa se inicializa sin parametros, lo unico que hay que saber es que ejecutables corer (El orden de ejecucion irrelevante):

- ./pistaEjecutable
- ./hormigaEjecutable

2) Existe un sistema con semaforos y memoria compartida para coordinar la inicializacion de procesos. Si por algun motivo se corta el programa durante la ejecucion, debe verificarse con ipcs si el semaforo y/o memoria compartida sigue activo/a. De estarlo es necesario borrar la cola de semaforos y la memoria compartida. De tener una ejecucion correcta, estos se limpian al finalizar de correr con exito el programa

3) Salen warnings a la hora de makear el programa, en su totalidad del framework de mensajes con el mensaje "type-punning" Al sacar el -Wall del make esto no pasa. Se recomienda sacarlo para ser mas prolijo el uso de makes

4) El programa realiza la carrera donde de forma sincronica van cediendose los turnos. El proceso que crea los hilos finaliza una vez las 3 hormigas lleguen a la meta. La pista tarda un poco mas en terminar, dado que una vez finalicen las hormigas, calcula a la ganadora de las mismas para mostrarlas en pantalla.

