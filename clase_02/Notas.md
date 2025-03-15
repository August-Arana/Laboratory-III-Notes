# Notas clase 2

Simplemente recordar que lo que decie los apuntes no es siempre tan correcto

Lo que vas a tener que hacer es agarrar clase por clase y desgrabar todo lo que el profe dice y hace de "diferente" con los apuntes.

Hoy vemos procesos
A partir de esta clase vamos a trabajar con mas de un proceso. Nuevamente, recordar que hay cosas que no son correctas a criterio del profesor y se tomara como valido lo que el mencione a lo largo de las clases.

Ejemplo, int main tiene que tener parametros.

### Fases de un programa

Codificacion
Compilacion
Ejecucion

Aquí se focalizará en la fase 3: cuando el programa se ejecuta, se sitúa en la memoria principal, por lo que el sistema operativo comienza a ejecutar sus instrucciones. La finalización de éste puede darse al cancelar su ejecución, o al terminar de ejecutarse las instrucciones del código.

### Definicion y recursos

Se puede pensar en un proceso como una porción de un programa en ejecución, o todo el
programa.
Los procesos son tareas separadas unas de otras con sus propios derechos y responsabilidades, **hacen uso de la CPU del sistema para realizar sus instrucciones** , de la memoria para almacenarse en él y a sus datos, además de usar ficheros y hasta los dispositivos conectados.
Por lo tanto, un proceso necesita recursos para llevar a cabo su tarea. Estos son:
•Tiempo de CPU.
•Memoria.
•Datos.
•Archivos y dispositivos de E/S.

Estos recursos se otorgan al proceso en el momento en que se crea, o bien se le asignan durante su ejecución.

\_\_
Se puede decir que un proceso es la unidad de trabajo de un sistema y el “sistema” consiste en una colección de procesos. Existen procesos que ejecutan el código del sistema operativo, y procesos de usuario que ejecutan código de algún usuario.

PERO
Los procesos son todos los tipos de tarea que solemos tener, que solemover, trabajar.

#### Seccion de videojuegos, el profesor pregunta y vemos el gorilas, tipo un "Worms world party" pero retro

Este es un juego opr turnos, pero la realidad es que estamos corriendo _un solo proceso_ Ya que el ejecutable se corrio una unica vez.

Esto es MUY importante de entender

Luego de esto, el profesor menciona que es probable que haya dos threads.

imaginemos que adentro de ese proceso hay subprocesos y por mas que estos existan

** Comentario de juego de tanques con dos procesos que se comunican entre ellos **

Ejemplo de conter, uno contra otro, los dis disparan al mismo tiempo. Ambos jugadores mueren?

**Lo que ensenia en esta seccion es que cuando se llama multitasking, multiproceso, multi what ever, JAMAS DOS PROCESOS CORREN AL MISMO TIEMPO**

Jamas dos sub procesos/hilos/threads corren al mismo tiempo. El que dispara primero es el que tiene ventaja

Entiendo que con lo que esta diciendo en esta seccion, se estaria refiriendo a que dos procesos que se comunican entre ellos enviandose seniales NO VAN a ejecutarse al mismo tiempo, ese intercambio de seniales o mensajes (Que serian como los disparos del Counter Strike) es de a uno a la vez.

Ni dos procesos ni dos hilos se ejecutan al mismo tiempo. Recordar que incluso en implementaciones de algunos sistemas operativos existe un "sistema escalonado" en los cuales las prioridades y el uso del cpu se va pasando a diferentes procesos. Recordar esto de Arquitectura de Computadores y Sistemas Operativos

Para casos donde tengo procesadores multinucleos ahi si, puedo ejecutar dos procesos al mismo tiempo.

### Comparacion con ser humano

En un proceso de computadora, los procesos tienen una pausa entre ellos (Tiempo de overhead, sistemas operativos).
En el cuerpo humano no hay pausas de procesos.

Esto es solo para recordar las pausas y tiempos muertos entre procesos.

Esto tiene que quedar claro, segun el profesor lo vamos a utilizar bastante en la materia y lo tenemos que tener en cuenta

## Proceso: estados

A medida que un proceso se ejecuta, cambia de estado. Cada proceso puede estar en uno
de los estados:
•Nuevo (new): el proceso se está creando.
•En ejecución (running): el proceso está en la CPU ejecutando instrucciones.
•Bloqueado (waiting, en espera): proceso esperando a que ocurra un suceso
(ejemplo: terminación de E/S o recepción de una señal).
•Preparado (ready, listo): esperando que se le asigne a un procesador.
•Terminado (terminated): finalizó su ejecución, por tanto no ejecuta más instrucciones y el Sistema Operativo (SO) le retirará los recursos que consume.

bloqueado -> ctrl-z

## Proceso: características

Un programa puede ejecutarse más de una vez, generándose más de una instancia del mismo programa. Un proceso incluye no sólo el programa que ejecuta, sino toda la información necesaria para diferenciar una ejecución del programa de otra. Con cada ejecución, el SO genera distintos identificadores a cada proceso:
•PID (Process ID): número de referencia único que tiene cada proceso que se inicia.
•UID, GID (User ID, Group ID): usuario y grupo al que pertenece el proceso. Estas
determinan los derechos del proceso a acceder a los recursos del sistema y ficheros.
• PPID (Parent Process ID): PID del proceso padre.
El contexto de un proceso es su estado, definido por:
•Su código.
•Los valores de sus variables de usuario globales y de sus estructuras de datos.
•El valor de los registros de la CPU.
•Los valores almacenados en su entrada de la tabla de procesos y en su área de usuario.
Y el contenido de sus pilas (stacks) de usuario y kernel.

## Procesos, comandos

ps -> lista de procesos del sistema.

usamos ps -f para trabajar

ps -f porque vemos los procesos vivos en una foto estatica del sistema.

### Ejecucion en primer y segundo plano

Primer plano te bloquea la terminal, es eso.

En la terminal, uno de primer plano lo matas con <Ctrl><c> o lo pausas con <Ctrl><Z>. La orden fg<CR> en terminal reanuda un proceso pausado

Para ejecutar un proceso en segundo plano desde la terminal se usa el caracter &. Ejemplo:

```bash
nautilus . &
```

Fin primer apunte.

Segundo apunte

## Librerias, pseudo librerias y makefile

### Intro del profesor

Vamos a entender la diferencia entre librerias y pseudolibrerias. Vamos a trbajar sobre lo que es el makefile. Vamos a trabajar en archivos .h (archivos header) donde van los protitpos. Los .c van a ir las funciones y todo el codigo en general.
Lo importante es tambien entender, por lo menos en esta clase, que vamos a trabajar con el archivo makefile para no estar tirando instrucciones de compilacion desde la linea de comandos, sino directamente utilizar el comando _make_.
Vamos a empezar a trabajar entendiendo esta diferenciacion, justamente a partir de la cual empieza toda la informatica en si.

Esto es, en sus origines se programaba con archivos .c y ya. Mas adelante se incorporo el .h. Despues algun visionario dijo de empezar a separar esos .c y .h para empezar a darle una modularidad y un determinado orden; esto fue lo que se termino transformando en las famosas clases y ahi es donde aparecio c++. Segun el profe, c++ ayuda en muchas cosas, pero en otras no le gusta, el prefiere que algunas cosas se programen en C, siguiendo metricas de c++, ejemplo, modularizando.

Vamos a ver como es, porque justamente esos .h (Que los estamos llamando como si fuera un estilo de clase) en verdad es una vinculacion entre diversos archivos .c. En esos .h vamos a colocar lo que queremos ver de afuera y lo que no queremos ver de afuera, que despues, aguas arriba, en lenguajes de alto nivel podemos llegar a compararlo con lo que es un metodo o variable publico y un metodo o variable privado.

Todo nace y parte de C.

### Librerías

Las librerías son un grupo de archivos que tienen una funcionalidad pre-construida, y que
pueden ser usadas por cualquier ejecutable. Las librerías contienen en su interior variables
y funciones.

A partir de este punto trabajamos con codigo.

Estos archivos contienen las especificaciones de diferentes funcionalidades que, al poder
incluirlas en el código, permitirá ahorrar gran cantidad de desarrollo y tiempo.

Nosotros en esta materia vamos a trabajar con framework. Esto es un framework. lo que tenemos aguas arribas, al fin y al cabo el framework esta impuesto en los entornos de compilacion. En java si hago Object.equals estamos re utilizando un framework de lo que es el entorno de compilacion.

Nosotros en C vamos a generar nuestro propio framework porque en C muchas de las cosas no estan, pero por mas que esten, tambien lo voy a hacer. Recordar override de toString en java, lo que terminas haciendo es construir tu propio framework con funciones propias o encpsulando metodos que ya estan. Tiene sentido.

### Como crear librerias propias

#### Utilizar librerias dentro del mismo directorio

Segun el profesor, una libreria en C es un .a o un .so. Lo que nosotros vamos a hacer con los .h son pseudo librerias.

Por ejemplo, se quiere crear una librería para las funciones del IPC de Linux y se desea incluir esta librería para probarla en otro archivo. Para esto se siguen los siguientes pasos:

##### Paso 1)

Se crea el archivo de cabecera con extensión “.h” en el mismo directorio del código
principal, éste archivo debe tener todos los prototipos de funciones y definiciones
de tipos de datos de la librería propia:

Empezamos siempre asi:

```c
#ifndef _FUNCIONES_H
#define _FUNCIONES_H
```

Luego del if not define ponemos el nombre del .h. Siempre colocamos el ifndef porque si ya esta definido no lo quiero definir de nuevo porque sino es redundante y me va a generar problemas.

**IMPORTANTE LO QUE VIENE AHORA!
NUNCA PONER #INCLUDE EN LOS .H**

```c
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <time.h>
#include <string.h>
```
obs: Solo si es necesario por un tipo de dato que no tenga. Hacerlo es motivo de reprobar un examen

```c
#define CLAVE_BASE 33
#define SEMAFORO0 0
#define LARGO_TMENSAJE 1024
```

Comentarios profesor: "Dentro de este archivo funciones.h tendria que poner los metodos de funciones.c y en el apunte muestra que este .h tiene un monton de #define que no van, a menos que lo este utilizando en quizas en funciones.h"

struct, tampoco deberia, a menos que sea un struct para utilizar en mi funciones.c

```c
typedef struct tipo_mensajes mensaje;
struct tipo_mensajes
{
    long    long_dest;
    int     int_rte;
    int     int_evento;
    char    char_mensaje[LARGO_TMENSAJE];
};
```

"Bueno, acá tenemos una estructura. Tampoco la debería de poner acá a menos que sea una estructura para utilizar en mis funciones.c. Pero en general, todo esto no lo vamos a utilizar Acá."

En esta parte, el apunte muestra luego un monton de funciones

```c
    key_t  creo_clave(int);
    void*  creo_memoria(int, int*, int);
    int    creo_semaforo(int);
    void   inicio_semaforo(int, int, int);
    void   levanta_semaforo(int, int);
    void   espera_semaforo(int, int);
    int    creo_id_cola_mensajes(int);
    int    borrar_mensajes(int);
    int    recibir_mensaje(int, long , mensaje*);
    int    enviar_mensaje(int, long, int, int, char*);
```

y el profesor dice:

De hecho, todo esto forma parte del framework. Voy a tener mi creo_clave y va a estar en clave.C y clave.H

No va a estar acá en funciones porque no voy a crear eso. Funciona alguna función que va a ser utilizada en todo el programa y no va a formar parte de un framework

Bueno, lo mismo, o va a ser el framework de funciones que en verdad no es un frameware. Son funciones globales que reutilizo. Todo eso va a estar en otro lado.

###### Otra explicacion sobre el apunte

En esta parte el profesor dice algo como "Si alguien pone los headers aca, no le voy a poner mal"

No entiendo.

###### Ejemplo 1

Imaginemos que tenemos la fucion creo_clave(int) con un tipo de dayo key_t que no esta, entonces dado esto, el unico include que deberia ir ahi es el de

```c
#include <sys/ipc.h>
```

Porque ese tipo de dato no esta en el .h (no definimos el struct aca)

###### Ejemplo 2

Ahora, imaginemos que creo_memoria() utiliza a creo_clave(), pero creo_clave no lo utilizo desde afuera (estaria recontra oculto), pero creo_memoria si, desde el main llamo a creo_memoria.
Es decir, desde main voy a tener que hacer un #include funciones.h

Pero, de nuevo, creo clave no se utiliza desde afuera, es algo interno de creo_memoria. Esto significa que creo_clave, quizas deberia estar el prototipo directamente en funciones.c porque no lo voy a ver desde afuera
Esto el profe no lo va a poner mal, porque no esta tan mal, pero si se entiende, esta funcion no deberia ser vista por lo demas si no la voy a utilizar.

Analogia: Es lo mismo que cuando se compila un metodo en alto nivel, es como si en java le pusiera public a creo_clave cuando solo se utiliza en la otra clase (lo cual en realidad esta mal!).

Creo_memoria es publica y creo_clave se utiliza dentro de creo_memoria (por obviedad, deberia ser privado, es lo que corresponde).

##### Paso 2)

Se crea el archivo del código de la librería; contiene el archivo de cabecera creado anteriormente y además incluye el código de todas las funciones que fueron escritas
en el archivo de cabecera:

Aca se muestra un archivo en el cual el profesor dice lo anterior, como creo_memoria utiliza creo_clave entonces nosotros no deberiamos definirla asi, nosotros vamos a manejarlo de otra manera, vamos a tener un framework de creo_clave que vamos a usar en otras cosas, por eso no va a queda acoplado a creo memoria.

Claro, lo que esta diciendo aca es que si tengo creo_memoria usando creo_clave y tengo ademas creo_semaforo, tambien usando creo_clave, seria ultra incorrecto codear esta misma funcion en ambos archivos, nuevamente, te estarias acoplando vos solo y te estas metiendo la soga al cuello.

Basicamente, lo que quiere es que no repitamos codigo.

##### Paso 3)

Definiciones.h si lo vamos a usar, basicamente metemos todas las definiciones utiles ahi adentro. Es como que se definen constantes que se van a utilizar en varios lados. Solo se ponen los define en definiciones.h

los structs, no, no deberian estar aca, deberian estar en otro lado. Global.c y global.h.

Global.\* va a tener variables globales y declaraciones. No va a tener funciones ni tampoco variables en los .h. Ahora lo vemos.

ESTO ESTA MAL, JAMAS JAMAS HACERLO: Declarar una variable en un .h

Las variables se declaran en los .c. En los .h se puede poner extern de la varialbe para que sea global y se pueda ver desde otro archivo.

##### Paso 4)

Llamada a la libreria.

Ejemplo supermercado.c y repositor.c: estos archivos son los que tienen el main.

Si usas "" para cargar librerias, sucede entonces que se van a buscar localmente esas librerias. Si usas <> las mismas se van a buscar en el directorio donde estan instaladas las librerias estandar de C.

##### Paso 5)

A partir de esta clase vamos a usar mas de un .c. recorda que en el momento de compilar vas a usar "-i./" para indicar el path en donde se encuentran tus headers. En esta materia usamos el mismo path donde tenemos los c.

Otro comentario, a partir de hoy no vamos a correr mas esto en el terminal, sino que vamos a correr un make donde se "resume" todo lo que va a pasar en la compilacion.

### Comando make

Make es una herramienta de gestión de dependencias usada en entornos Linux. Cuando el código se compone de varios archivos de código fuente, es muy práctica para compilar de una forma automatizada todo lo que necesitas y pasarle a GCC las opciones necesarias. Además, make sabrá qué cosas hay que recompilar en caso de que hagas cambios, algo bastante práctico cuando el proyecto es grande. Además de eso, make entiende los formatos o extensiones. Por ejemplo, si es un hola.c sabe que le debe encargar la tarea a gcc, mientras que si es un hola.cpp se lo encomendará a g++, etc.

La utilidad make requiere de un archivo, makefile, que define un conjunto de tareas a ejecutar y describe como compilar un programa.

#### Archivo makefile

Un archivo makefile básicamente se distingue en cuatro tipos básicos de declaraciones:

- Comentarios
- Variables.
- Reglas explicitas.
- Reglas implícitas.

Las reglas explícitas le indican a make que archivos dependen de otros archivos, así como los comandos requeridos para compilar un archivo en particular.
Las reglas implícitas son similares que las explicitas, pero con la diferencia que indican los comandos a ejecutar, sino que make utiliza las extensiones de los archivos para determinar que comandos ejecutar.

Cree un archivo makefile con el siguiente contenido:

Archivo makefile:

```c

\# Esto es un comentario.

CC= gcc-4.1

all : clean repositor supermercado

supermercado : supermercado.c funciones.h definiciones.h funciones.o
    $cc -o supermercado supermercado.c funciones.o

repositor : repositor.c funciones.h definiciones.h funciones.o
    $cc -o repositor repositor.c funciones.o

funciones.o : funciones.c funciones.h
    $cc -c funciones.c

clean:
    rm -rf *o supermercado repositor

```

##### Variables

En este case, CC es utilizado como una variable. A lo largo del resto del makefile el profesor recomienda agregar el simbolo $ delante para llamarla (de hecho creo que no va a funcionar sino)
Tambien puedo tener archivos .c dentro de las variables.

##### Comando all

uso: all : objetivo1 objetivo 2

all puede no estar, pero en esta materia lo vamos a usar. All lo que hace es que cuando ponemos make, si hay all utiliza los objetivos que estan definidos

##### Objetivos

Arriba:
Tiene primero unas dependencias que no son obligatorias
Abajo:
<Tab>$cc -o {Nombre ejecutable} archivos.c archivos.o

Se utiliza .o porque primero compila los object. Ahi faltan todos los flags que vimos la clase pasada.

Viendo el caso anterior, va a suceder que cada objetivo me genera un ejecutable. Estos ejecutables, entiendo, van a ser utilizados.

Pregunta del profesor: Tengo dos objetivos que cada uno genera un ejecutable, cuantos ejecutables voy a tener?

Cada objetivo genera un ejecutable (es lo que dice tu codigo!)

Memorizar esto:
Si yo tengo un repositor y el porgrama/ejercicio/examen pide 'che, voy a tener tres repositores'. Cuantos archivos .c voy a tener? y cuantos objetivos voy a tener?

Voy a tener 1 archivo c, 1 objeto repositor y tres procesos repositor (Recorda, se ejecuta tres veces y tenes tres procesos).

#### Compilacion usando make

Esto es

```bash
$ make
```

y ya esta

#### Reglas de make

Es posible hacer que make sea más listo escribiendo un fichero, uno de cuyos nombres por defecto es makefile, y decirle en él qué cosas debe hacer y cómo.
En ese fichero se incluirán cosas como:
objetivo: dependencia1dependencia2 ...
\<tab\>comando1
\<tab\>comando2

“objetivo” es lo que se desea construir. Puede ser el nombre de un ejecutable, el nombre de una librería o cualquier palabra inventada. Para este ejemplo, se usa: all, supermercado, repositor, funciones.o y clean.

dependencia\<i\> es el nombre de otro objetivo que debe hacerse antes que el propio, o bien ficheros de los que depende el objetivo. En el ejemplo, las dependencias serían los ficheros fuente, ya que para hacer el ejecutable se necesitan todos esos fuentes y, si se los toca, posiblemente se deberá rehacer el ejecutable.

\<tab\> es un tabulador. Es importante que ahí se ponga un tabulador, porque sino el fichero no se lee correctamente.

comando\<i\> es lo que se tiene que ejecutar para construir el objetivo. Se irán ejecutando estos comandos en secuencia. Puede ser cualquier comando de shell válido. (cc, rm, cp, ls, o incluso un script que se haya hecho).

## Apunte 3

Pasaje de valores por linea de comandos.

```c
int main(int argc, char *argv[])
// argc es la cantidad de argumentos
// argv es un array con todos los argumentos
// el nombre del programa es el primer valor del array.
```
Es importante mencionar que los parametros son tomados como palabras, como ascii dentro del archivo.

los parametros que se insertan en ./programa 1 2 3 4

### Seccion programacion

A partir de aca se inicia toda la programacion, ver archivos anexos.

mis archivos .c siempre van a tener .h

no nos interesan los sistemas de representacion

global: variables globales y delcaraciones de estructuras
jamas se inicializa valores globales.

extern -> se usa para decir que las variables son globales

Vamos a trabajar con variables dinamicas y estaticas
\*num -> es variable dinamica, lo esta pasando por referencia, aca el profe dijo "no es del todo correcto decir que es una referen"

Tenemos que tener cuidado y liberar memoria si usamos memoria dinamicas
Tenemos que

el 0x es para indicar que es exa

strcpy, linux se toma el atrvimiento de limpiar la variable antes de usarla.

uniste.h

nos sirve esa libreria porque de ahi sacamos sleep en segundos o microsleep que trabaja en microsegundos

TAREA TAREA TAREA

- tener archivos que menciono el profe (ver grabaciones)
-
