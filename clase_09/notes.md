# Notas sobre uso de `pthread` y `pthread_mutex` en C

## 🧵 1. Declaración de variables necesarias

### Mutex (Semáforo de exclusión mutua)

```c
pthread_mutex_t mutex;
```

Se declara una variable global con un tipo nuevo `pthread_mutex_t` que actúa como **sección crítica protegida** entre hilos. Un `mutex` hace que solo un hilo a la vez acceda a una sección del código. Viene a cumplir la funcion de un semaforo.

### Identificador y atributos del hilo

```c
pthread_t idHilo;
pthread_attr_t atributos;
```

* `pthread_t idHilo`: identificador único del hilo que se va a crear. Tambien es un tipo de dato nuevo.
* `pthread_attr_t atributos`: estructura para configurar cómo se comportará el hilo. Tengo que estudiarlo mas a esto.

---

## ⚙️ 2. Inicialización de estructuras

### Inicializar el mutex

```c
pthread_mutex_init(&mutex, NULL);
```

Aca justamente se inicializa el `mutex` declarado al principio. El segundo parámetro es `NULL`, lo que significa que se usan los atributos por defecto (re ver esto).

### Inicializar atributos del hilo

```c
pthread_attr_init(&atributos);
```

Los atributos, se ve, no se pueden utilizar asi como asi, sino que tambien hay que inicializarlos. Esto sospecho que es parecido a lo que pasa con los semaforos, que deben estar inicializados para qeu todo el mundo los vea y tengan entonces un lugar comun al cual apuntar. Algo similar debe estar pasando aca.

---

## 🔧 3. Configuración del hilo

### Estado "joinable" del hilo

```c
pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);
```

Esto le dice al sistema que el hilo creado estará en estado **joinable**, es decir, el hilo principal podrá esperar a que el hilo hijo termine usando el comando `pthread_join`. Esta es la forma adecuada si queres **sincronizar el final del hilo hijo** antes de que termine el `main`.
Funciona como una "declaracion" de que es lo que vas a hacer con este thread.

---

## 🚀 4. Creación del hilo

```c
pthread_create(&idHilo, &atributos, funcionThread, NULL);
```

Y aca arranca la magia, esa funcion lanza la ejecución del hilo. Los parámetros son:

* `&idHilo`: dirección donde se almacenará el ID del nuevo hilo.
* `&atributos`: atributos configurados para el hilo.
* `funcionThread`: función que ejecutará el hilo (debe tener la firma `void *func(void *)`).
* `NULL`: parámetro opcional que puede recibir la función (en este caso no se usa ninguno).

---

## 🔁 5. Uso del mutex como control de acceso

Dentro de ambos hilos (el principal y el creado), se utiliza:

```c
pthread_mutex_lock(&mutex);
// sección crítica
pthread_mutex_unlock(&mutex);
```
Esto asegura que **solo un hilo a la vez pueda ejecutar esa sección del código**, garantizando que no se impriman mensajes simultáneamente o se corrompan recursos compartidos.

---

## ⏳ 6. Esperar a que termine el hilo

```c
pthread_join(idHilo, (void **)&valorDevuelto);
```

* `pthread_join` es una función importantisima. Primero tenes que entender que **es bloqueante**: en este ejemplo, el hilo principal se detiene hasta que el hilo especificado (`idHilo`) termina su ejecución.
* El segundo parámetro permite **recuperar el valor retornado** por el hilo (en este caso, `"Listo"`).

El otro hilo anuncia el fin de la ejecucion con lo siguiente:
* `pthread_exit((void *)"Listo")`  
Fijate que se esta 'catapultando' el valor listo, el cual es el valor final capturado por la funcion pthread_join explicada antes.

---

## 🧹 7. Finalización

Después de `pthread_join`, el hilo principal continúa su ejecución. Ya es seguro liberar recursos y finalizar el programa.

---

## 💡 Resumen conceptual

Este programa muestra cómo **crear un hilo**, **proteger una sección crítica con un mutex**, y **esperar su finalización**. Es un ejemplo típico de sincronización entre procesos concurrentes en C.

---

































No olvidar las indicaciones y las prioridades.
Ver la clase, no olvidar limpiar memorias

En esta clase, el profesor hace una observacion acerca del ejercicio entregado.

para aprobar la cursada, el profesor no pide bi direccionalidad, de ese modo la sincronizacion es mas sencilla. ahora, para el final si, tiene que haber una direccionalidad.

ejemplo carrera liebre

recordar ejemplo de tablero y jugadores en el juego de la oca.

Ver el ENUM si es necesario o no



-- empieza el tema del dia, threads

ojo con los apuntes, falta el anpersen en el nombre de la funcion
En otros lenguajes, existen callbacks, pero C es mas poderoso en este sentido.


busca delegados vs interfaces en C#


no olvidar de esta clase:

primero: si estamos en tiempo de ejecucion y queremos ver el proceso padre y los procesos hijo (hilos) y quiero ver el id, tenemos que utilizar ps -eLf podemos ver los sub procesos.
Igual, lo podes ver en el manual

segundo: para verlo, se hace mientras corremos. Lo podemos ver ver en top, pero no tenemos para ver hijos de procesos.

recordar que todos los hilos comparten cosas, ejemplo, comparten el bloque control de proceso.


IMPORTANTE: cuando trabajemos con mutex

COLOCARLO EN GLOBAL LOS MUTEX!!

Global.h
extern pthread_mutex_t mutex;

Global.c
pthread_mutex_t mutex;


recuerden por favor, POR FAVOR, el mutex corresponde a cada proceso, o sea, que dos procesos entre ellos no se van a frenar entre ellos usando mutex. OJO DONDE PONES LAS cosaso

LO TENES QUE USAR SABIENDO QUE CORRESPONDE A CADA PROCESO INTERNO, NO ES COMO UN SEMAFORO.


en el makefile tenes que agregar algo nuevo, sino no te va a compilar


