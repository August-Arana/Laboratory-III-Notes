JAMAS HACER INCLUDE DE .C

cuando desarrollas, lo importante es que cualquier persona 

Comentarios sobre primer apunte

No es lo c para linux que C en si mismo, porque el primero puede hacer llamadas asl sistema operativo y estas no funcionarian en otro entorno sin el sitema operativo.

0) Recordar hacer chmod 755 de tus main a ejecutar

1) int main, siempre pasarle los dos parametros que vamos a usar siempre.

2) Jamas una variable va declarada despues de una funcion

3) Todo programa tiene que tener un main y todo proceso tiene que tener un main, no hace falta que se llame main.c

4) gcc -o: -o me crea el programa objeto, no el 'output'

5) .a o .so son las verdaderas librerias, .h son para le profesror pseudolibrerias

6) Jamas hacer include de un .c, jamas un include adentro de un .h, amenos que sea mandatorio y yo requiera el tipo dato, jamas un .h que no utilice

7) Corchete de un lado es lo mismo que asterisco del otro:
*arch
arch[]

8) Algunas banderas que vamos a usar
- -pedantic-errors
- -std=gnu98
- -Wall
- -Werror

9) sleep me permite tener mi proceso vivo