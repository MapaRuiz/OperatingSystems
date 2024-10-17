
# Comunicación Bi-Direccional con Pipes Nombrados en C

Este repositorio contiene un ejemplo de comunicación bi-direccional entre un cliente y un servidor utilizando pipes nombrados (FIFOs) en C. El cliente envía mensajes al servidor, que los invierte y devuelve al cliente. La comunicación continúa hasta que se ingresa el mensaje "end".

## Estructura del Proyecto

- `cliente.c`: Código fuente del cliente.
- `servidor.c`: Código fuente del servidor.

## Compilación

Para compilar el cliente y el servidor, asegúrate de tener un compilador de C instalado, como `gcc`. Puedes compilar ambos archivos de la siguiente manera:
`
- gcc cliente.c -o cliente
- gcc servidor.c -o servidor
`

## Ejecución

Ejecutar el Servidor: Abre una terminal y ejecuta el servidor. Esto creará el FIFO y comenzará a escuchar mensajes del cliente.

- ./servidor

Ejecutar el Cliente: Abre otra terminal y ejecuta el cliente. Esto te permitirá enviar mensajes al servidor.

- ./cliente

Enviar Mensajes: En la terminal del cliente, ingresa mensajes para enviar al servidor. Para finalizar la comunicación, ingresa end.

## Descripción de Funcionamiento

`Cliente`
- Función: El cliente envía mensajes al servidor y espera respuestas. Cuando el usuario ingresa "end", el cliente cierra la conexión y finaliza.
- Comunicación: Se establece a través de un FIFO en /tmp/fifo_twoway. El cliente envía mensajes y recibe las respuestas inversas del servidor.
- Programa "clienteBidireccional": Este programa implementa un cliente que se comunica de manera bi-direccional a través de un pipe nombrado (FIFO). El cliente envía mensajes al servidor, recibiendo respuestas hasta que el usuario ingresa "end". Al hacerlo, el cliente se cierra. Utiliza el archivo FIFO en "/tmpfifo_twoway" para establecer la comunicación.

`Servidor`
- Función: El servidor recibe mensajes del cliente, los invierte y envía la cadena invertida de vuelta. Se detiene cuando recibe el mensaje "end".
- Comunicación: Utiliza el mismo FIFO que el cliente. El servidor imprime el mensaje recibido y la respuesta invertida.
- Programa "serverBidireccional": Este programa implementa un servidor que se comunica de manera bi-direccional a través de un pipe nombrado (FIFO). El servidor espera recibir mensajes del cliente, los invierte y envía de vuelta al cliente. Si el servidor recibe el mensaje "end", se cierra. Utiliza el archivo FIFO en "/tmp/fifo_twoway" para establecer la comunicación.

## Notas
- Asegúrate de tener permisos para crear y acceder al FIFO en la ruta especificada.
- El uso de sleep(2) en el servidor asegura que el cliente tenga tiempo suficiente para leer el mensaje enviado.
