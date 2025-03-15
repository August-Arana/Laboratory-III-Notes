

1-Para su ejecucion completa es necesario abrir minimo 2 terminales, de querer hacerse la prueba con más aviones se requieren unas 4 terminales

2- se recomiendo el uso del comando sudo su antes de ejecutar los comandos que copilaran y correran el programa

3- El codigo a la hora de ejecutar el make crea 2 archivos ejecutables
Uno de nombre "panel" y otro de nombre "avion"
tambien crea un archivo de texto vuelos.txt donde se almacena informacion
durante la ejecucion

2- los dos "main" son panel.c y avion.c

3- Es importante ejecutar en cierto orden el ejercicio asi tambien con ciertos parametros. El orden y sus valores de ejecucion son los siguientes:

 1- En primer lugar ejecutaremos 
        ./avion 1 
        ./avion 2 
        ./avion 3
        


 2- Por ultimo lugar debe ejecutarse el panel sin ningun parametro adicional

	./panel 

4- antes de cada ejecución se debe hacer un make para evitar errores 

5- el programa debe cortar despues de 10 entradas de cada avion, en caso de ser muy largo se puede terminar antes con el comando por teclado ctrl c encada una de las terminales
