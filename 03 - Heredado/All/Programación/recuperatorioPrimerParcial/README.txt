Hola ! este es el recuperatorio del alumno Lucas Uriel Ramos

:[Consideraciones]:

1- El codigo a la hora de ejecutar el make crea 2 archivos ejecutables
Uno de nombre "panel" y otro de nombre "equipo"
tambien crea un archivo de texto equipos.txt donde se almacena informacion
durante la ejecucion

2- los dos "main" son panel.c y equipo.c

3- Es importante ejecutar en cierto orden el ejercicio asi tambien con ciertos parametros. El orden y sus valores de ejecucion son los siguientes:

 1- En primer lugar ejecutaremos dos procesos de equipo los cuales deberan seguir los siguientes parametros. El orden de ejecucion de los equipos es indistinto. Se recomienda incluir las mayusculas en el nombre

	./equipo "Argentina" 
	./equipo "Japon" 
	
	- NOTA: Se recomienda ejecutar ambos procesos en un lapso de segundos, dado que, el srand funcionara con de la misma forma en ambos programas, generando asi un empate al ejecutar ambos procesos casi en simultaneo. 

 2- Por ultimo lugar debe ejecutarse el panel sin ningun parametro adicional

	./panel 


4- De querer volver a ejecutar el programa, debera volver a makearse. En su defecto, eliminar el archivo de texto equipos.txt y volver a crearlo. Es indispensable para el funcionamiento del programa

5- En caso de empate no habra resolucion adicional


