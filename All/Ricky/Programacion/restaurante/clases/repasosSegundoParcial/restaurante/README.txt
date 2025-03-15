Consideraciones a tener en cuenta a la hora de correr el programa:

1) el programa se inicializa sin parametros, lo unico importante es su orden de ejecucion

2) el programa primero debe ejecutar ./panelEjecutable y luego ./animalEjecutable

3) se posee un flag de memoria para que el panel espere al animal. El panel no arranca hasta que el proceso de hilos genere los valores para los mismos

4) Salen warnings a la hora de makear el programa, en su totalidad del framework de mensajes con el mensaje "type-punning" Al sacar el -Wall del make esto no pasa. Se recomienda sacarlo para ser mas prolijo el uso de makes

5) De equivocarse a la hora de ejecutar o por un error inesperado, es posible que sea necesario utilizar ipcrm -M y -Q para volver a ejecutar el programa para que el flag de memoria vuelva a ser 0


