/*********************
Autor: Mapa Rodriguez
Materia: Sistemas operativos
Fecha: 10-10-24
Tema: Parcial 2ndo corte
- Aplicar los conceptos de procesos y comunicación entre procesos
- Descripcion: Programa que recibe por parametro dos archivos que contienen un arreglo de enteros
separados por espacio junto a sus tamanos correspondientes, y a partir de ellos junto a el uso
de la fnc fork() y pipes (tuberias) se comunica con la informacion de las diferentes sumatorias que se
pueden hacer con estos datos teniendo como resultado 3 pipes = 1 con la suma del primer archivo, otro
con la suma del segundo y el 3ero con la suma de ambos, rotando la informacion entre procesos.
Para conseguir el ejecutable solo hace falta ubicarse donde estan esta serie de archivos y escribir
el comando make que ya ejecutara el Makefile, y posteriormente ejecutarlo con los parametros
que se indicaron al inicio ./ejecutable N1 archivo00 N2 archivo01
*********************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

// Definir las rutas de los FIFO - tmp pa que no importen los permisos jeje
#define FIFO1 "/tmp/fifo1"
#define FIFO2 "/tmp/fifo2"
#define FIFO3 "/tmp/fifo3"

//Fnc para leer el archivo y guardar en el arreglo correspondiente
//Parametros:  nombre del archivo a leer, el arreglo donde se va a guardar y el tamano del arreglo
void leerArchivo(const char* nombreArchivo, int* arreglo, int cantidad) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        exit(1);
    }

    for (int i = 0; i < cantidad; i++) {
        if (fscanf(archivo, "%d", &arreglo[i]) != 1) {
            perror("Error al leer el archivo");
            fclose(archivo);
            exit(1);
        }
    }

    fclose(archivo);
}

//Fnc para calcular la suma total de los elementos de un arreglo
//Parametros:  El arreglo donde se va a guardar y el tamano del arreglo
int calcularSuma(int* arreglo, int cantidad) {
    int suma = 0;
    for (int i = 0; i < cantidad; i++) {
        suma += arreglo[i];
    }
    return suma;
}
//En el grandHijo, leo el archivo, hago el calculo y lo mando por el pipe correspondiente que es el primero
//parametros: el archivo 00 y el tamano del arreglo
void grandHijo(const char* archivo00, int N1) {
    int* arregloA = (int*)malloc(N1 * sizeof(int));
    if (arregloA == NULL) {
        perror("Error al asignar memoria para arregloA");
        exit(1);
    }

    leerArchivo(archivo00, arregloA, N1);
    int sumaA = calcularSuma(arregloA, N1);
    printf("GrandHijo: [pid %d] Suma del archivo00 = %d\n", getpid(), sumaA);

    int fd = open(FIFO1, O_WRONLY);
    if (fd < 0) {
        perror("Error al abrir fifo1 para escritura");
        exit(1);
    }
    if (write(fd, &sumaA, sizeof(sumaA)) == -1) {
        perror("Error al escribir en fifo1");
    }
    close(fd);  // Cerramos el FIFO después de la escritura

    free(arregloA);
    exit(0);  // Terminar el proceso GrandHijo
}
//En el segundoHijo, leo el archivo, hago el calculo y lo mando por el pipe correspondiente que es el segundo
//parametros: el archivo 01 y el tamano del arreglo
void segundoHijo(const char* archivo01, int N2) {
    int* arregloB = (int*)malloc(N2 * sizeof(int));
    if (arregloB == NULL) {
        perror("Error al asignar memoria para arregloB");
        exit(1);
    }

    leerArchivo(archivo01, arregloB, N2);
    int sumaB = calcularSuma(arregloB, N2);
    printf("SegundoHijo: [pid %d] Suma del archivo01 = %d\n", getpid(), sumaB);

    int fd = open(FIFO2, O_WRONLY);
    if (fd < 0) {
        perror("Error al abrir fifo2 para escritura");
        exit(1);
    }
    if (write(fd, &sumaB, sizeof(sumaB)) == -1) {
        perror("Error al escribir en fifo2");
    }
    close(fd);  // Cerramos el FIFO después de la escritura

    free(arregloB);
    exit(0);  // Terminar el proceso SegundoHijo
}

//Al hacer primer fork, si el pId me dio 0 me vengo pa aca
//La func se va a encargar de hacer los fork para obtener el segundo hijo y el grand hijo, los manda a que calculen
//y con lo que le devuelvan calcula la suma total de los dos arreglos
//Parametros: Ambos arhivos junto a sus tamanos
void primerHijo(const char* archivo00, int N1, const char* archivo01, int N2) {
    printf("PrimerHijo: [pid %d] Creando procesos hijos\n", getpid());

    //Aqui ejecuto dos fork pa poder sacar al segundo y al gran hijo
    pid_t pid = fork();
    if (pid < 0) {
        perror("Error al crear el proceso GrandHijo");
        exit(1);
    } else if (pid == 0) {
        segundoHijo(archivo01, N2);  // Ejecución del proceso SegundoHijo
    }

    pid = fork();
    if (pid < 0) {
        perror("Error al crear el proceso SegundoHijo");
        exit(1);
    } else if (pid == 0) {
        grandHijo(archivo00, N1);  // Ejecución del proceso GrandHijo

    }

    sleep(0.5); // Me espero un ratito a que ambos procesos hayan escrito en los FIFOs

    // Leer las sumas de los named pipes.
    int sumaA = 0, sumaB = 0;
    int fd1 = open(FIFO1, O_RDONLY);
    if (fd1 < 0) {
        perror("Error al abrir fifo1 para lectura");
        exit(1);
    }
    if (read(fd1, &sumaA, sizeof(sumaA)) == -1) {
        perror("Error al leer desde fifo1");
    }
    close(fd1);  // Cerramos el FIFO después de la lectura

    int fd2 = open(FIFO2, O_RDONLY);
    if (fd2 < 0) {
        perror("Error al abrir fifo2 para lectura");
        exit(1);
    }
    if (read(fd2, &sumaB, sizeof(sumaB)) == -1) {
        perror("Error al leer desde fifo2");
    }
    close(fd2);  // Cerramos el FIFO después de la lectura

    // Calcular la suma total.
    int sumaTotal = sumaA + sumaB;
    printf("PrimerHijo: [pid %d] Suma total de ambos arreglos = %d\n", getpid(), sumaTotal);

    // Enviar la suma total al padre.
    int fd3 = open(FIFO3, O_WRONLY);
    if (fd3 < 0) {
        perror("Error al abrir fifo3 para escritura");
        exit(1);
    }
    if (write(fd3, &sumaTotal, sizeof(sumaTotal)) == -1) {
        perror("Error al escribir en fifo3");
    }
    close(fd3);  // Cerramos el FIFO después de la escritura

    exit(0);  // Terminar el proceso PrimerHijo
}
//Al hacer primer fork, si el pId me dio >0 me vengo pa aca
//Esta fnc se va a encargar de recibir los calculos de los 3 procesos desde gracias al Fifo 3 del cual el primer hijo
//ya se encargo de llenar
//Parametros: no necesita ninguno pues la conexion ya esta dada x el pipe
void padre() {
    sleep(1); // Me espero un tantito a que todo lo del 1er hijo se haya ejecutado

    // Leer la suma total del PrimerHijo desde fifo3.
    int sumaTotal = 0;
    int fd3 = open(FIFO3, O_RDONLY);
    if (fd3 < 0) {
        perror("Error al abrir fifo3 para lectura");
        exit(1);
    }
    if (read(fd3, &sumaTotal, sizeof(sumaTotal)) == -1) {
        perror("Error al leer desde fifo3");
    }
    close(fd3);  // Cerramos el FIFO después de la lectura

    printf("Padre: [pid %d] Suma total final = %d\n", getpid(), sumaTotal);
}

//Programa principal con su total de argumentos para fijar que la entrada sea la correcta
int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Uso: %s N1 archivo00 N2 archivo01\n", argv[0]);
        return 1;
    }

    // Leer argumentos y pasarlos a lo que deben de ser
    int N1 = atoi(argv[1]);
    char* archivo00 = argv[2];
    int N2 = atoi(argv[3]);
    char* archivo01 = argv[4];

    // Crear los named pipes.
    unlink(FIFO1); // Eliminar fifo1 si existe
    if (mkfifo(FIFO1, 0666) == -1) {
        perror("Error al crear fifo1");
        exit(1);
    }
    unlink(FIFO2); // Eliminar fifo2 si existe
    if (mkfifo(FIFO2, 0666) == -1) {
        perror("Error al crear fifo2");
        unlink(FIFO1);  // Eliminar si falla el segundo
        exit(1);
    }
    unlink(FIFO3); // Eliminar fifo3 si existe
    if (mkfifo(FIFO3, 0666) == -1) {
        perror("Error al crear fifo3");
        unlink(FIFO1); // Eliminar si falla el tercero
        unlink(FIFO2); // Eliminar si falla el tercero
        exit(1);
    }

    printf("Padre: [pid %d] Creando proceso PrimerHijo\n", getpid());

    pid_t pid = fork();
    if (pid < 0) {
        perror("Error al crear el proceso PrimerHijo");
        exit(1);
    } else if (pid == 0) {
        primerHijo(archivo00, N1, archivo01, N2);  // Ejecución del proceso PrimerHijo
    } else {
        padre();  // Ejecución del proceso Padre
    }

    // Remover los named pipes después de su uso.
    unlink(FIFO1);
    unlink(FIFO2);
    unlink(FIFO3);

    return 0;
}
