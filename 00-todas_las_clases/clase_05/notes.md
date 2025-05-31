Bueno, doy un pequenio repaso de como usar los semaforos, porque necesito agilidad en su uso.

## 1 y 2

Estos dos se hacen juntos. La idea es tener un semaforo unico e inequivoco. Esto se hace todo junto en tu framework. La obtencion de la clave es con una parte de tu frame y la creacion del semaforo es otra:

Obtener clave:
Es lo que tiene ftok adentro y usa ls

```c
key_t creo_clave() {
    key_t clave;
    clave = ftok("/bin/ls", CLAVE);
    if ( clave == (key_t)-1){
       printf("No puedo conseguir clave semaforo");
       exit(0);
    }
    return clave;
}
```
Creacion de semaforo
```c
int creo_semaforo(){

    key_t clave = creo_clave(33);
    int id_semaforo = semget(clave, 1, 0600|IPC_CREAT);

    if(id_semaforo == -1){
        printf("Error: no puedo crear semaforo\n");
        exit(0);
    }
    return id_semaforo;
}
```

Esto lo vas a tener en tu framework, lo importante de estas dos funciones es que a partir de ahora, obtenes el id del semaforo y es sobre el cual tus procesos van a trabajar.
Entender las funciones, dejalo y leelo en el apunte, ahora lo que importa es hacer que esto funcione.

## 3 - Proceso que inicia semaforo
Resulta que un proceso debe dar aviso al uso del semaforo con lo siguiente

```c
void inicia_semaforo(int id_semaforo, int valor){
    semctl(id_semaforo, 0, SETVAL, valor);
}
```
"valor" es lo que tenemos que poner en verde o en rojo, con 1 o 0 respectivamente. Verde implica que el semaforo va a estar creado. Es importante notar que, el proceso que va a iniciar el semaforo es el productor en nuestro caso


## 4 - Primer uso de semaforos, decrementar, bloquear
en realidad se da por la funcion int semop (int, struct sembuf *, size_t), que recibe 3 parametros, id semaforo, un array de operaciones y el numero de elemtnos en el array.
La estructura del segundo parametor posee:
- short sem_num que es el índice del array, 0
- short sem_op que es el valor en el que se quiere decrementar el semáforo, 1 o -1
- short sem_flg son flags que afectan a la operación, 0

En el framework esto es:

```c
void espera_semaforo(int id_semaforo){
    struct sembuf operacion;
    printf("Espera SEMAFORO \n");
    operacion.sem_num = 0;
    operacion.sem_op = -1; /*decrementa el semaforo en 1*/
    operacion.sem_flg = 0;
    semop(id_semaforo,&operacion,1);
}
```

A partir de ahora, espera semaforo va a restar operaciones del semaforo que se este utilizando. Y esta avisando de bloquear todo lo que viene despues

## 5 - Segundo uso, incrementar, desbloquear
Esto es, cuando el proceso termina lo que debe hacer, levanta el semaforo

```c
void levanta_semaforo(int id_semaforo){
    struct sembuf operacion;
    printf("Levanta SEMAFORO \n");
    operacion.sem_num = 0;
    operacion.sem_op = 1; /*incrementa el semaforo en 1*/
    operacion.sem_flg = 0;
    semop(id_semaforo,&operacion,1);
}
```

Deduccion de haber mostrado en clase: Lo que seguramente fallo fue las configuraciones apuradas, para mi el ejercicio de semaforo estaba bien, solo fallo el framework.

### Acerca de que es lo que esta pasando durante la ejecucion

Claro, lo que tenes que entender y lo que se ve en la consola es que los semaforos en algun momento bloquean a los procesos. Recorda esto:

- Ambos procesos estan mirando el mismo semaforo
- Recordar, super importante, que cuando el semaforo se hace negativo, (porque el proceso LO HIZO) negativo, entonces ese proceso pasa a una cola de espera
- La idea es que el semaforo permita dar orden:
    Inicia productor -> crea semaforo (1)
    Productor resta semaforo (0), empieza a ejecutar
    Inicia consumidor
    Consumidor resta semaforo (-1)
        Consumidor en lista de espera
    Productor termina, levanta semaforo (0)
        Consumidor sale de lista de espera, empieza a ejecutar
    Productor resta semaforo (-1)
        Productor en lista de espera
    consumidor termina, levanta semaforo (0)
        Productor sale de lista de espera, empieza a ejecuta
    consumidor resta semaforo (-1)
        consumidor entra en lista de espera
    productor termina. levanta semaforo(0)
        consumidor sale de lista de espera, empieza a ejecutar
    productor resta semaforo (-1)
        productor entra en lista de espera

y asi...
    

### Acerca de imprimir archivos

Algo muy inteligente que aparece en el ejercicio de semaforos es esto:

```c
char cadena[LARGO];
FILE *productor;

productor = fopen("producto.txt", "a");
sprintf(cadena, "PRODUCTO-%04d-%04d\n", nro_partida, nro_producto);
fprintf(productor,"%s",cadena);
```

Es decir, muy inteligentemente, primero se pegan todas las variables adentro de cadena y es entonces "cadena" lo que se imprime adentro del archivo. con el framework esto seria:

```c
char cadena[LARGO];
inAbrirArchivo("producto.txt", "a");
sprintf(cadena, "PRODUCTO-%04d-%04d\n", nro_partida, nro_producto);
inEscribirArchivo("%s",cadena);
```

Tene eso presente, es bastante util