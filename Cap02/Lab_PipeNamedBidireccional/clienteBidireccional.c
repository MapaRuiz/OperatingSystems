/*********************
Autor: Mapa Rodriguez
Materia: Sistemas operativos
Fecha: 17-10-24
Tema: pipeNamed (Comunicación Bi-Direccional)
- Cliente
Descripción:
Este programa implementa un cliente que se comunica de manera bi-direccional 
a través de un pipe nombrado (FIFO). El cliente envía mensajes al servidor, 
recibiendo respuestas hasta que el usuario ingresa "end". Al hacerlo, el 
cliente se cierra. Utiliza el archivo FIFO en "/tmp/fifo_twoway" para 
establecer la comunicación.
*********************/

#define FIFO_FILE "/tmp/fifo_twoway"  // Definición de la ruta del pipe nombrado

#include <stdio.h>      // Biblioteca para funciones de entrada/salida
#include <sys/stat.h>  // Biblioteca para definiciones de estructuras de sistema
#include <sys/types.h> // Biblioteca para tipos de datos del sistema
#include <fcntl.h>     // Biblioteca para operaciones de archivos
#include <unistd.h>    // Biblioteca para funciones de POSIX
#include <string.h>    // Biblioteca para manipulación de cadenas

int main() {
    int fd;                     // Descriptor de archivo para el FIFO
    int end_process;           // Variable para verificar si el usuario quiere salir
    int stringlen;             // Longitud de la cadena ingresada por el usuario
    int read_bytes;            // Cantidad de bytes leídos del FIFO
    char readbuf[80];          // Buffer para almacenar la cadena leída/escrita
    char end_str[5];           // Cadena que indica el fin del proceso ("end")

    printf("FIFO_CLIENT: Send messages, infinitely, to end enter \"end\"\n");
    
    // Abre el FIFO para lectura y escritura; lo crea si no existe
    fd = open(FIFO_FILE, O_CREAT | O_RDWR);

    // Copia la cadena "end" en la variable end_str
    strcpy(end_str, "end");

    // Bucle infinito para enviar y recibir mensajes
    while (1) {
        printf("Enter string: ");  // Solicita al usuario que ingrese una cadena
        fgets(readbuf, sizeof(readbuf), stdin);  // Lee la cadena ingresada

        // Obtiene la longitud de la cadena leída
        stringlen = strlen(readbuf);

        // Reemplaza el salto de línea al final de la cadena con un terminador nulo
        readbuf[stringlen - 1] = '\0';

        // Compara la cadena ingresada con "end"
        end_process = strcmp(readbuf, end_str);

        //printf("end_process is %d\n", end_process); // Línea de depuración (comentada)
        
        // Si el usuario no ingresó "end"
        if (end_process != 0) {
            write(fd, readbuf, strlen(readbuf));  // Envía la cadena al FIFO
            printf("FIFOCLIENT: Sent string: \"%s\" and string length is %d\n", readbuf, (int)strlen(readbuf));
            
            // Lee la respuesta del FIFO
            read_bytes = read(fd, readbuf, sizeof(readbuf));
            readbuf[read_bytes] = '\0';  // Agrega el terminador nulo al final de la cadena leída
            
            // Imprime la respuesta recibida
            printf("FIFOCLIENT: Received string: \"%s\" and length is %d\n", readbuf, (int)strlen(readbuf));
        } else {
            // Si el usuario ingresó "end", se envía la cadena y se cierra el FIFO
            write(fd, readbuf, strlen(readbuf));
            printf("FIFOCLIENT: Sent string: \"%s\" and string length is %d\n", readbuf, (int)strlen(readbuf));
            close(fd);  // Cierra el descriptor del FIFO
            break;      // Sale del bucle
        }
    }
    return 0;  // Termina el programa
}
