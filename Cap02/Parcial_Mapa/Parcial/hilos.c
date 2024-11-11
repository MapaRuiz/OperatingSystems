/*********************
Autor: Mapa Rodriguez
Materia: Sistemas Operativos
Fecha: 11-07-24
Descripción: Este programa en C utiliza la biblioteca POSIX para crear y manejar 5 hilos de manera concurrente, asegurando que cada hilo imprima su salida en un orden específico. Cada hilo imprime un mensaje de inicio, simula una tarea interna hasta 300 (imprimiendo la primera y la ultima) y luego imprime un mensaje de finalización. Para garantizar que los mensajes se impriman en orden (del hilo 1 al 5), se emplea una variable global ordenActual que controla cuál hilo puede imprimir en cada momento.Las funciones clave utilizadas en el programa son:

pthread_create: Para crear y lanzar los hilos.
pthread_join: Para sincronizar y esperar a que cada hilo finalice.
pthread_mutex_lock y pthread_mutex_unlock: Para proteger el acceso a la variable ordenActual y evitar condiciones de carrera.
imprimirMensaje: Función ejecutada por cada hilo, que controla la tarea y la impresión de mensajes en el orden deseado.
*********************/

#include <stdio.h>         // Librería estándar para operaciones de entrada y salida
#include <pthread.h>       // Librería para el manejo de hilos POSIX
#include "hilos.h"         // Archivo de encabezado que declara la función imprimirMensaje

extern pthread_mutex_t BLOQUEO;  // Declaración externa del mutex, definido en main.c
extern int ordenActual;          // Variable de control de orden definida en main.c

// Función que será ejecutada por cada hilo
void *imprimirMensaje(void *arg) {
    int id = *(int *)arg;  // Convierte el argumento a un entero que representa el ID del hilo

    while (1) {
        pthread_mutex_lock(&BLOQUEO);      // Bloquea el acceso a la sección crítica

        if (ordenActual == id) {           // Verifica si es el turno de este hilo
            printf("\nHilo %d iniciado\n", id);

            for (int i = 0; i < 300; i++) {	
                if(i==0){printf("%d - ", i);}
		if(i==299){printf("%d", i);}
            }

            printf("\nHilo %d finalizado\n", id);

            ordenActual++;                 // Incrementa el orden para el siguiente hilo
            pthread_mutex_unlock(&BLOQUEO);  // Libera el mutex
            break;                         // Sale del bucle una vez que ha completado su tarea
        }
        
        pthread_mutex_unlock(&BLOQUEO);    // Libera el mutex si no es su turno
    }

    return NULL;                           // Termina el hilo
}

