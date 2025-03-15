

1-Para su ejecucion completa es necesario abrir 3 terminales

2- se recomiendo el uso del comando sudo su en cada terminal antes de ejecutar los comandos que copilaran y correran el programa

3- El codigo a la hora de ejecutar el make crea 2 archivos ejecutables
Uno de nombre "panel" y otro de nombre "equipo"
tambien crea 3 archivos de texto panel.txt argentina.txt y japon.txt donde panel se encarga de guardar y mostrar el partido 
y los dos ultimos guardan los datos de jugada de los respectivos equipos


2- los dos "main" son panel.c y equipo.c

3- Es importante ejecutar en cierto orden el ejercicio asi tambien con ciertos parametros. El orden y sus valores de ejecucion son los siguientes:

 1- En primer lugar ejecutaremos,
        ./equipo 1 -> argentina
        ./equipo 2 -> japon
 2- Por ultimo lugar debe ejecutarse el panel sin ningun parametro adicional
	./panel 

4- antes de cada ejecución se recomienda debe hacer un make para evitar errores, pero tambien se puede ejecutar en seguida los 3 procesos en el orden ya mencionado

5- el programa debe cortar despues de que un equipo haya anotado 11 puntos o ambos puesto que puede existir empate

