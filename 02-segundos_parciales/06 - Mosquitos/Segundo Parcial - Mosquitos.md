# Parcial 2

## Examen Segundo parcial

### Consignas

**La Carrera Espiral:**  
En una carrera circular, con forma de espiral, 2 mosquitos compiten por sobrevivir.  
El espiral tiene una distancia de 95 metros. Los mosquitos quieren llegar a la meta antes que el humo los alcance.  
Aún así, es una carrera por turnos (todos tienen que terminar sus turnos si quieren sobrevivir).  
Los mosquitos avanzan de entre 3 y 6 metros, mientras que el humo avanza entre 1 y 4 metros (estos valores que van saliendo son aleatorios).  
Si el humo supera alguno de los mosquitos, es que ese mosquito no sobrevivió y no continua la carrera.

Se cuenta con 2 procesos. Todo el tiempo deben mostrarse los eventos y lo que va aconteciendo en los dos procesos.  
Lo recomendable sería contar con el proceso **panel/tablero**, y por otro lado proceso **jugadores/mosquitos y humo**.

- **Panel/tablero**: debe informar lo que sucede luego de que un mosquito avance, el humo avance, y/o no sobrevivan o lleguen a destino.  
  Pero siempre informar por turno, no solo una vez al final.

Debe utilizar **Threads**, **cola de mensajes** para la comunicación, **mutex** para el sincronismo.  
Cada **300ms** el sistema debe estar interactuando un nuevo turno.

Usar los eventos que crea necesario y las variables y estructuras que precise.  
Borrar los mensajes anteriores, para empezar de 0.

Se recomienda que deba comenzar el juego presionando una tecla cuando los dos procesos estén corriendo, utilizando **memoria compartida** (o sea cualquiera de los dos procesos debería poder ejecutarse primero).  
O usar un bucle en cada caso. En el peor de los casos informar qué proceso debe correrse primero o tratar de dar orden e informarlo en **README**.

Concentrarse en un **MVP, funcional**.  
Utilizar **Makefile**.

---

### Consignas

1. Leer todo el enunciado.  
2. Resolver el ejercicio.  
3. Enviar la resolución como respuesta a esta actividad en archivo comprimido **.tar** o **.tar.gz**

---

### Condiciones de corrección  
*(si no se cumple lo siguiente, no se corrige)*

- El programa debe compilar sin errores.  
- El programa debe correr sin errores de memoria.  
- Debe estar correctamente identado.  
- Utilizar constantes.

---

### Puntos a tener en cuenta

- Los nombres de las variables deben ser descriptivos de su función (sobre todo en el `main`).  
- Comentar el código todo lo posible.  
- Toda variable o arreglo definido en forma dinámica debe ser liberado al finalizar el programa.
