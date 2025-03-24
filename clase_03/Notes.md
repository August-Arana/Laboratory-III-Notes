# Clase 3

Hoy vamos a ver varias cosas, entre ellas, caracteres, errores, archivos, con archivos vamos a comunicar dos procesos, inicialmente, por medio de archivos.

El profe tambien menciona ahora el orden de las clases. Es importante estar al dia (A ponerse con estructura de datos y metodos)

clase4: diferenciacion, trabjar con 2 o mas procesos.
clase 5: Semaforos, para darle sincronismo a lo que es la comunicacion entre los procesos, por meido de los archivos.
6: Examen pre parcial, ojo aca.
7: Examen parcial -> 16 abril

## Errores
En errores hay que estar duchos, no titubear en examen, es MUY FUERTE ESTO.

profe lee el apunte...
...
Muestra errores del apunte

Algunos errores... pueden pasar de largo por el compilador y no verse.

Ahora hace una mencion de cosas sobre los compiladores, todos los lenguajes compilan.

Sigue leyendo...
Errores de tiempo de ejecucion ->

Tenemos que tener cancha con debugging, no debe ser un error para nosotros.

Estar duchos con debugging, lo volvio a decir

// Lo siguiente lo dijo, no se a que se refiere
compilar con /* (?) 


Cadenas de texto
Lee el apunte.

Ojo, hay funciones que pueden detectar algo con 0x00, cuidado en esos casos.



Segun lo que dice el profe, hay que usar sprintf de tres argumentos.

NO USAMOS FLOAT Y DOBLE EN ESTA MATERIA

Hasta ahora, venimos haciendo un repaso de cosas que ya deberias saber agus...


strlen detecta hasta 0x00, es decir, esa combinacion de caracteres lo corta.
sizeof me devuelve el tamanio real.


Nosotro vamos a manejar otra cosa.

funciones que se toman atribuciones, no pasa solo en C, pasa en todos los lenguajes.


Esta mal usar estas funciones? No, pero siempre tomar recaudos.

Siempre sacar la memoria con memset


memset se corta por 0x00

Siempre usar memset antes de la variable

De nuevo, con estas cosas no tenemos que tener inconvenientes, tiene que salir rapido y tenes que ser agil.


## archivos
Son el primer recurso qwue trabajamos para ipc.

Hay funciones extra que no vamos a ver, las podemos usar, pero no es recomendado.


No hacer asignaciones dentro d eun comparador


Ejemplo de archivo: esta mal, esta todo junto y se tiene que modularizar

