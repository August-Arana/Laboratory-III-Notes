Estructura de cliente con hasta 20 productos, puede tener entre 1 y 20 productos

como le pasa el cliente desde el derivador a la caja?

    - envio mensaje con el cliente segun n items
    - envio el cliente a todos, cada caja elige procesar o no

primera opcion suena logica, sino el derivador no estaria derivando, sino repitiendo a todos.

- Inicia Derivador, o inicia Cajeros, el orden no afecta

Derivador
    - Borra mensajes
    __
    - Crea Cliente
    - Pide Descripcion producto a cliente
    - sortea los X cantidad productos
    - imprime al cliente en memoria compartida
    - envia mensaje al cajero correspondiente
    - Se queda esperando respuesta de cajero
    - vuelve a empezar
    __
    - limpia memoria
    - Fin

Cajeros
    - recibe mensaje
    - bloquea mutex
    - Lee cantidad de productos en contenido mensaje
    - Busca en memoria donde se imprimio la estructura cliente
        - Abre archivo
        - imprime desc en archivo
        - imprime precio en archivo
        - suma total en variable
        - imprime __ en archivo
        - imprime total
        - imprime \n\n
        - Cierra archivo
    - Envia mensaje a derivador
    - libera mutex
