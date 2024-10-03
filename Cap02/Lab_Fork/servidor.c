/*********************
Autor: Mapa Rodriguez
Materia: Sistemas operativos
Fecha: 03-10-24
Tema: Fork - Lab pipeNamed(Comunicacion Uni-Direccional)
- Server
 *********************/

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_FILE "MYFIFO"    // Definición del nombre del archivo FIFO

int main(){
    int fd;            // Descriptor de archivo para el FIFO
    char readbuf[80];  // Buffer para almacenar los mensajes recibidos (máximo 80 caracteres)
    char end[10]; 	   // Cadena para comparar con el mensaje de fin ("end")
    int to_end;		   // Variable para verificar si el mensaje es "end"
    int read_bytes;    // Número de bytes leídos del FIFO

    /* Create the FIFO if it does not exist */
    printf("\n >>> INICIO SERVIDOR <<<\n");
    // Permisos 0640: Lectura y escritura para el propietario, solo lectura para el grupo
    mknod(FIFO_FILE, S_IFIFO|0640, 0); //2-R 4-W 1-X
    // Definición del mensaje de fin
    strcpy(end, "end");

    // Bucle principal del servidor, que sigue recibiendo mensajes
    while(1) {
        // Abrir el FIFO solo para lectura
        fd = open(FIFO_FILE, O_RDONLY);
        // Leer datos del FIFO
        read_bytes = read(fd, readbuf, sizeof(readbuf));
        // Agregar el carácter de fin de cadena
        readbuf[read_bytes] = '\0';
        // Imprimir el mensaje recibido
        printf("Received string: \"%s\" and length is %d\n", readbuf, (int)strlen(readbuf));
        // Comparar con el mensaje "end" para saber si se debe finalizar
        to_end = strcmp(readbuf, end);
        // Si el mensaje es "end", salir del bucle
        if (to_end == 0) {
          // Cerrar el archivo FIFO
          close(fd);
          break;
        }
    }
    return 0;
}

