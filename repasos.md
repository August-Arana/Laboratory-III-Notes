### Punteros
Recorda el uso de punteros, se usa para apuntar a direcciones de memoria puntuales y modificar el contenido de esas direcciones de memoria:

#### Fundamentos:
##### Declaracion
```c
// DECLARACION
int *ptr; // Esta es la forma de DECLARAR un puntero con su tipado. Esto ahora te permitiria guardar una direccion

int number = 8;
int *ptr = &numero; // & se usa para obtener la direccion de alguna variable, entonces ahora podes guardar la direccion de esa variable en el puntero de tu interes
```
##### Usos basicos
Vos entonces tambien podias imprimir diferentes datos en cuanto alos punteros
```c
    printf("Valor de numero: %d\n", numero); // Impresion basica de un numero
    printf(ptr);// resulta que esta forma de imprimir... te va a dar el valor intrinseco del puntero. Como el puntero guarda una direccion, este printi te devuelve la direccion que tiene adentro.

    Ahora, distinto es:
    printf("Valor de numero usando el puntero: %d\n", *ptr);
    //ptr te guardo una direccion, pero hace:
    //*ptr te permite ver el valor que guarda la direccion que esta adentro de ptr

    // entonces

    ptr; // es una variable que guarda la direccion de algo
    *ptr; //me muestra el valor que hay adentro de la direccion que esta adentro de ptr
```
No es dificil, sino que es confuso, nuevamente
ptr -> guardo una direccion (la direccion de una casa)
\*ptr -> veo lo que hay adentro de esa casa

##### Modificar valores
```c
// Lo mas basico es modificar el valor de otra variable externa:
int numero = 8;
int *ptr = &numero;

*ptr = 10;

// printf numero ahora me daria 10

```

##### Punteros y arrays
// Una cosa importante y teorica, es que el funcionamiento de los arrays tiene algo de punteros:

```c
    int numeros[] = {10, 20, 30, 40};
    int *ptr = numeros; // Equivalente a &numeros[0]
    // Los nombres de los arreglos en si mismos son punteros al primer elemento.

    printf("Primer elemento: %d\n", *ptr);     // 10
    printf("Segundo elemento: %d\n", *(ptr+1)); // 20


```

### Archivos
#### fopen
Aca pasa algo interesante. La direccion de fopen es:
```c
FILE *fopen(const char *filename, const char *mode);
```
Con esa definicion, sucede que lo que estaria necesitando recibir la funcion, es un puntero char con el nombre del archivo a leer. Pero ademas, tambien pasa lo siguiente:

```c
fopen("archivo.txt", "r");
```
Tambien se puede pasar directamente el nombre del archivo. Porque es esto posible? Pues resulta que lo que está pasando internamente es que "archivo.txt" se almacena en algún lugar de la memoria como una cadena constante y se pasa como un puntero al primer carácter de esa cadena.
Esto sera uno de esos "atrevimientos" que linux se toma segun el profesor?

Internamente el compilador:

```c
const char *temp = "archivo.txt";
fopen(temp, "r");
```



```c
```
