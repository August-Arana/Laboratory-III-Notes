# Segundo Examen - Parcial

## Consignas

### Compras en el super

En un supermercado, se destina por medio de un sistema de control (llamado **"super derivador"**) a cada caja que corresponda cada comprador según la cantidad de productos que haya elegido (aleatorio de 1 hasta 20). Todos los compradores hacen una única fila y se cuenta con **3 cajas**.

Cada caja tiene una cantidad mínima y máxima de unidades permitidas y por donde cada comprador deberá realizar su pago, dependiendo de sus unidades:

* **Caja 1**: de 1 a 5 unidades
* **Caja 2**: de 6 a 10 unidades
* **Caja 3**: de 11 a 20 unidades

---

Se cuenta con **2 procesos**:

1. Uno para el **"super derivador"**
2. Otro proceso para las **N cajas** (en este caso 3)

---

Se contará con un **array (arreglo) de estructuras**, en la que cada estructura cuenta con:

* el **precio**
* la **descripción del producto**

(Puede utilizar 20 productos —que es el máximo— o, si lo cree conveniente, utilizar memoria dinámica u otro método con/sin array/estructuras donde pueda colocar el precio y la descripción. Puede usar los mismos archivos si lo desea).

---

### Requisitos del sistema

* Realizar un **menú para el "super derivador"** que permita el **ingreso por teclado** de:

  * la descripción del producto
  * el precio

* Dependiendo de la cantidad de unidades, se dirigirá a cada caja (**cada hilo de caja**).

* Para **comunicar el derivador con las cajas**, puede utilizar:

  * **cola de mensajes** (por ejemplo `MSJ_CAJA+i`) o
  * **memoria compartida**

* Cada **100 ms**, cada caja debe chequear si tiene un **nuevo comprador**.

* La caja correspondiente debe **mostrar el precio total** que debe pagar el comprador, y **no debe repetirse el mensaje/precio anterior** (ósea, debe ser nuevo el comportamiento. Si el precio da igual, no es problema).

---

### Archivos de salida

Al finalizar la compra, en un **archivo con el nº de caja** (ósea 3 archivos en total, uno por cada caja), se debe **guardar el total que se vendió al momento**, con un **totalizador** que sume las ventas totales que se van realizando.

Ejemplo:

* Si el total de la compra anterior fue **\$500**, y la nueva es **\$1000**, el archivo debe quedar con **\$1500**, y así sucesivamente por cada archivo de cada caja.

---

### Consideraciones adicionales

* Se debe **mostrar la actividad de cada proceso**
* Usar los **eventos que crea necesario**
* Utilizar **Makefile** con la estructura de archivos vista en la cursada

---
