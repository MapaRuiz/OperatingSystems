/*********************
Autor: Mapa Rodriguez
Materia: Sistemas Operativos
Fecha: 11-07-24
Descripción: Este programa en C utiliza la biblioteca POSIX para crear y manejar 5 hilos de manera concurrente, asegurando que cada hilo imprima su salida en un orden específico. Cada hilo imprime un mensaje de inicio, simula una tarea interna hasta 300 (imprimiento la primera y la ultima) y luego imprime un mensaje de finalización. Para garantizar que los mensajes se impriman en orden (del hilo 1 al 5), se emplea una variable global ordenActual que controla cuál hilo puede imprimir en cada momento.Las funciones clave utilizadas en el programa son:

pthread_create: Para crear y lanzar los hilos.
pthread_join: Para sincronizar y esperar a que cada hilo finalice.
pthread_mutex_lock y pthread_mutex_unlock: Para proteger el acceso a la variable ordenActual y evitar condiciones de carrera.
imprimirMensaje: Función ejecutada por cada hilo, que controla la tarea y la impresión de mensajes en el orden deseado.
*********************/

#include <stdio.h>         // Librería estándar de entrada y salida
#include <stdlib.h>        // Librería para funciones de control de memoria y conversiones
#include <pthread.h>       // Librería para manejo de hilos POSIX
#include "hilos.h"         // Archivo de encabezado que declara la función imprimirMensaje

pthread_mutex_t BLOQUEO;      // Declaración del mutex, que será accesible en otros archivos
int ordenActual = 1;          // Variable global para controlar el orden de ejecución de los hilos

int main() {
    pthread_t hilos[5];       // Arreglo para almacenar los identificadores de 5 hilos
    int ids[5];               // Arreglo de IDs de los hilos, que se pasarán como argumentos
    int error;                // Variable para almacenar el código de error al crear hilos

    pthread_mutex_init(&BLOQUEO, NULL);  // Inicialización del mutex para la sección crítica

    // Bucle para crear los hilos
    for (int i = 0; i < 5; i++) {
        ids[i] = i + 1;       // Asigna un ID único a cada hilo, de 1 a 5
        error = pthread_create(&hilos[i], NULL, imprimirMensaje, &ids[i]);  // Crea un hilo que ejecuta imprimirMensaje con su ID
        if (error != 0) {     // Verifica si la creación del hilo falló
            printf("\nError en la creación del hilo: [%d]", error);  // Muestra un mensaje de error si no se creó el hilo
        }
    }

    // Bucle para sincronizar y esperar a que cada hilo finalice
    for (int i = 0; i < 5; i++) {
        pthread_join(hilos[i], NULL);  // Espera a que cada hilo termine
    }

    pthread_mutex_destroy(&BLOQUEO);  // Destruye el mutex para liberar recursos
    return 0;               // Finaliza el programa con éxito
}

