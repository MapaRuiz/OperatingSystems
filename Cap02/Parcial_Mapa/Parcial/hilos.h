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

#ifndef HILOS_H
#define HILOS_H

#include <pthread.h>

extern pthread_mutex_t BLOQUEO;  // Declaración del mutex como variable externa
extern int ordenActual;          // Declaración de la variable de orden como externa

void *imprimirMensaje(void *arg);  // Declaración de la función que ejecuta cada hilo

#endif

