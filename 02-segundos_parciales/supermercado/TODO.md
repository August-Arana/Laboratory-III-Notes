Estructura de cliente con hasta 20 productos, puede tener entre 1 y 20 productos

como le pasa el cliente desde el derivador a la caja?

    - envio mensaje con el cliente segun q items
    - envio el cliente a todos, cada caja elige procesar o no

primera opcion suena logica, sino el derivador no estaria derivando, sino repitiendo a todos.

derivador crea cliente
    - Limpia memoria
    - le agrega X productos a cliente
    - sortea los X productos dentro del array de productos
    - imprime al cliente en memoria compartida
    - envia al cajero correspondiente

Cajero recibe mensaje
    - Lee cantidad de productos
    - recorre la seccion de memoria donde se imprimio el cliente
        - por cada item
            - imprime desc en archivo
            - imprime precio en archivo
            - suma total en variable
        - imprime __ en archivo
        - imprime total
        - imprime \n\n
    - limpiar memoria


    
