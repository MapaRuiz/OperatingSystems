/*********************
Autor: Mapa Rodriguez
Materia: Sistemas operativos
Fecha: 03-10-24
Tema: Fork - Lab pipeNamed(Comunicacion Uni-Direccional)
- Cliente
 *********************/

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_FILE "MYFIFO" // Definición del nombre del archivo FIFO
int main()
{
    int fd;				// Descriptor de archivo para el FIFO
    int end_process;	// Indicador de finalización
    int stringlen;		// Longitud de la cadena a enviar
    char readbuf[80];	// Buffer para almacenar el mensaje a enviar
    char end_str[5];	// Cadena con el mensaje "end"

    printf("\n >>> INICIO CLIENTE <<<\n");
    printf("FIFO_CLIENT: Send messages, infinitely, to end enter \"end\"\n");
    // Intentar abrir el FIFO solo para escritura
    fd = open(FIFO_FILE, O_CREAT|O_WRONLY);
    // Definir el mensaje de finalización "end"
    strcpy(end_str, "end");

    // Bucle principal del cliente
    while (1) {
      // Solicitar al usuario que introduzca un mensaje
        printf("Enter string: ");
        fgets(readbuf, sizeof(readbuf), stdin);
        // Eliminar el salto de línea del final de la entrada
        stringlen = strlen(readbuf);
        readbuf[stringlen - 1] = '\0';
        // Comparar el mensaje con "end"
        end_process = strcmp(readbuf, end_str);

        printf("end_process is %d\n", end_process);
        if (end_process != 0) {
          // Enviar el mensaje al FIFO e imprimir
            write(fd, readbuf, strlen(readbuf));
            printf("Sent string: \"%s\" and string length is %d\n", readbuf, (int)    strlen(readbuf));
        } else {
          // Enviar el mensaje al FIFO e imprimir
            write(fd, readbuf, strlen(readbuf));
            printf("Sent string: \"%s\" and string length is %d\n", readbuf, (int)    strlen(readbuf));
          //Cerrar el FIFO y salir del bucle
            close(fd);
            break;
        }
    }
    return 0;
}	
