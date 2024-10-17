/*********************
Autor: Mapa Rodriguez
Materia: Sistemas operativos
Fecha: 17-10-24
Tema: pipeNamed (Comunicación Bi-Direccional)
- Servidor
Descripción:
Este programa implementa un servidor que se comunica de manera bi-direccional 
a través de un pipe nombrado (FIFO). El servidor espera recibir mensajes del 
cliente, los invierte y envía de vuelta al cliente. Si el servidor recibe 
el mensaje "end", se cierra. Utiliza el archivo FIFO en "/tmp/fifo_twoway" 
para establecer la comunicación.
*********************/

#define FIFO_FILE "/tmp/fifo_twoway"  // Definición de la ruta del pipe nombrado

#include <stdio.h>      // Biblioteca para funciones de entrada/salida
#include <sys/stat.h>  // Biblioteca para definiciones de estructuras de sistema
#include <sys/types.h> // Biblioteca para tipos de datos del sistema
#include <fcntl.h>     // Biblioteca para operaciones de archivos
#include <unistd.h>    // Biblioteca para funciones de POSIX
#include <string.h>    // Biblioteca para manipulación de cadenas

// Prototipo de la función que invierte una cadena
void reverse_string(char *); 

int main() {
    int fd;                     // Descriptor de archivo para el FIFO
    char readbuf[80];          // Buffer para almacenar la cadena leída
    char end[10];              // Cadena que indica el fin del proceso ("end")
    int to_end;                // Variable para verificar si se debe cerrar el servidor
    int read_bytes;            // Cantidad de bytes leídos del FIFO

    /* Crea el FIFO si no existe */
    mkfifo(FIFO_FILE, S_IFIFO | 0640); // Crea el FIFO con permisos 0640 //2-R 4-W 1-X
    strcpy(end, "end");        // Copia la cadena "end" en la variable end

    // Abre el FIFO para lectura y escritura
    fd = open(FIFO_FILE, O_RDWR);

    // Bucle infinito para recibir mensajes
    while (1) {
        // Lee del FIFO
        read_bytes = read(fd, readbuf, sizeof(readbuf));
        readbuf[read_bytes] = '\0';  // Agrega el terminador nulo al final de la cadena leída

        // Imprime el mensaje recibido y su longitud
        printf("FIFOSERVER: Received string: \"%s\" and length is %d\n", readbuf, (int)strlen(readbuf));
        
        // Compara la cadena leída con "end"
        to_end = strcmp(readbuf, end);

        // Si el mensaje es "end", cierra el FIFO y sale del bucle
        if (to_end == 0) {
            close(fd);  // Cierra el descriptor del FIFO
            break;      // Sale del bucle
        }

        // Invierte la cadena recibida
        reverse_string(readbuf);
        
        // Imprime la cadena invertida y su longitud
        printf("FIFOSERVER: Sending Reversed String: \"%s\" and length is %d\n", readbuf, (int)strlen(readbuf));
        
        // Envía la cadena invertida de vuelta al FIFO
        write(fd, readbuf, strlen(readbuf));
        
        /*
         *       sleep - Esto asegura que el otro proceso lea el mensaje; 
         *       de lo contrario, este proceso podría recuperar el mensaje.
         */
        sleep(2);
    }
    
    return 0;  // Termina el programa
}

// Función para invertir una cadena
void reverse_string(char *str) {
    int last, limit, first;   // Variables para el control de la inversión
    char temp;                // Variable temporal para el intercambio

    last = strlen(str) - 1;  // Índice del último carácter
    limit = last / 2;        // Punto medio de la cadena
    first = 0;               // Índice del primer carácter

    // Bucle para intercambiar los caracteres
    while (first < last) {
        temp = str[first];     // Almacena el carácter actual
        str[first] = str[last]; // Intercambia los caracteres
        str[last] = temp;     // Completa el intercambio
        first++;              // Avanza al siguiente carácter
        last--;               // Retrocede al carácter anterior
    }
    
    return;  // Termina la función
}
