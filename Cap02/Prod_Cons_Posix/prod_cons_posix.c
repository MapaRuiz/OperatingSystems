/*********************
Autor: Mapa Rodriguez
Materia: Sistemas operativos
Fecha: 10-24-24
Tema: Hilos POSIX
- Problema Productor y Consumidor
*********************/

#include <stdio.h>            // Inclusión de la biblioteca estándar para entrada/salida.
#include <stdlib.h>           // Inclusión de la biblioteca estándar para funciones generales como malloc, free, etc.
#include <pthread.h>         // Inclusión de la biblioteca para manejo de hilos POSIX.
#include <unistd.h>          // Inclusión de la biblioteca que proporciona acceso a las funciones de POSIX, como sleep().

// Variables compartidas
int counter = 0;            // Contador que representa la cantidad de elementos en el buffer.
int max = 4;                // Valor máximo que representa la capacidad del buffer.

pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER; // Inicializa un mutex para proteger el acceso al contador.
pthread_mutex_t condp_mutex = PTHREAD_MUTEX_INITIALIZER;    // Inicializa un mutex para la condición del productor.
pthread_mutex_t condc_mutex = PTHREAD_MUTEX_INITIALIZER;    // Inicializa un mutex para la condición del consumidor.

pthread_cond_t condVarProd = PTHREAD_COND_INITIALIZER;      // Inicializa una variable de condición para el productor.
pthread_cond_t condVarCons = PTHREAD_COND_INITIALIZER;      // Inicializa una variable de condición para el consumidor.

// Función que representa el comportamiento del hilo productor.
void *productor() {
    while(1) {  // Bucle infinito que permite al productor trabajar continuamente.
        pthread_mutex_lock(&condp_mutex);  // Bloquea el mutex para controlar la condición del productor.
        while(counter >= 10) {              // Mientras el contador alcance o supere 10, espera.
            pthread_cond_wait(&condVarProd, &condp_mutex); // Espera la señal del consumidor.
        }
        pthread_mutex_unlock(&condp_mutex); // Libera el mutex después de la verificación.

        pthread_mutex_lock(&counter_mutex);  // Bloquea el mutex para modificar el contador.
        counter++;                            // Incrementa el contador (producción de un nuevo elemento).
        pthread_cond_signal(&condVarCons);   // Señala al consumidor que hay un nuevo elemento disponible.
        printf("Soy productor %d valor contador = %d\n", (int)pthread_self(), counter); // Imprime el estado del productor.
        pthread_mutex_unlock(&counter_mutex); // Libera el mutex después de modificar el contador.
        pthread_mutex_unlock(&condp_mutex);   // Libera el mutex de condición del productor.

        if(counter == 5)                      // Si el contador llega a 5, duerme por 1 segundo.
            sleep(1);
    }
}

// Función que representa el comportamiento del hilo consumidor.
void *consumidor() {
    while(1) {  // Bucle infinito que permite al consumidor trabajar continuamente.
        sleep(1);  // Duerme por 1 segundo antes de intentar consumir.
        pthread_mutex_lock(&condc_mutex); // Bloquea el mutex para controlar la condición del consumidor.
        while(counter <= 0) {              // Mientras el contador sea menor o igual a 0, espera.
            pthread_cond_signal(&condVarProd); // Señala al productor que puede producir más.
            pthread_cond_wait(&condVarCons, &condc_mutex); // Espera la señal del productor.
        }
        pthread_mutex_unlock(&condc_mutex); // Libera el mutex después de la verificación.

        pthread_mutex_lock(&counter_mutex);  // Bloquea el mutex para modificar el contador.
        if(counter > 0) {                     // Verifica si hay elementos para consumir.
            printf("Soy consumidor %d valor contador = %d\n", (int)pthread_self(), counter); // Imprime el estado del consumidor.
            counter--;                        // Decrementa el contador (consumir un elemento).
            pthread_cond_signal(&condVarProd); // Señala al productor que hay espacio disponible.
        }
        pthread_mutex_unlock(&counter_mutex); // Libera el mutex después de modificar el contador.
        pthread_mutex_unlock(&condc_mutex);    // Libera el mutex de condición del consumidor.
    }
}

int main() {
    pthread_t proHilo[max], conHilo[max]; // Arreglos de hilos para productores y consumidores.
    int i;                                 // Variable de iteración.

    for(i = 0; i < 5; i++) {               // Crea 5 hilos productores.
        pthread_create(&proHilo[i], NULL, &productor, NULL);
        pthread_create(&conHilo[i], NULL, &consumidor, NULL); // Crea 5 hilos consumidores.
    }

    for(i = 0; i < 5; i++) {               // Espera a que todos los hilos terminen.
        pthread_join(proHilo[i], NULL);   // Une el hilo productor.
        pthread_join(conHilo[i], NULL);   // Une el hilo consumidor.
    }

    return 0;                             // Finaliza el programa.
}
