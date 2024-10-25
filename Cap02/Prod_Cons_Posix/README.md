
# Productor-Consumidor con POSIX Threads en C

Este repositorio contiene una implementación del problema clásico de productor-consumidor utilizando **POSIX threads (pthread)** en C. Los hilos productores y consumidores acceden y modifican una variable compartida (`counter`), que representa el "almacén" de productos, sincronizándose mediante **mutex** y **variables de condición**.

## Estructura del Proyecto

- `productor_consumidor.c`: Código fuente que implementa el problema productor-consumidor utilizando pthreads.

## Compilación

Para compilar el programa, asegúrate de tener un compilador de C instalado, como `gcc`. Usa el siguiente comando para compilar el código fuente:

```
gcc -pthread -o productor_consumidor productor_consumidor.c
```

El flag `-pthread` es esencial para habilitar la biblioteca de POSIX threads.

## Ejecución

Para ejecutar el programa una vez compilado, utiliza el siguiente comando:

```
./productor_consumidor
```

Esto iniciará el programa, creando hilos de productores y consumidores que se comunicarán a través de la variable compartida `counter`.

## Descripción de Funcionamiento

`Productor`
- Función: Los hilos productores incrementan el valor de `counter` cuando hay espacio en el "almacén" (cuando `counter < 10`).
- Sincronización: Los productores utilizan un mutex y una variable de condición para asegurarse de que no produzcan más productos cuando el "almacén" está lleno.
- Comportamiento: Cuando `counter` alcanza un valor de 10, los productores se bloquean esperando a que los consumidores consuman productos para liberar espacio.

`Consumidor`
- Función: Los hilos consumidores decrementan el valor de `counter` cuando hay productos disponibles (cuando `counter > 0`).
- Sincronización: Los consumidores utilizan un mutex y una variable de condición para esperar hasta que haya productos disponibles para consumir.
- Comportamiento: Los consumidores se bloquean cuando `counter` llega a 0, esperando a que los productores produzcan más.

## Detalles de Sincronización

El programa usa las siguientes primitivas de sincronización de POSIX:
- **pthread_mutex_t**: Protege el acceso a la variable compartida `counter`, evitando condiciones de carrera.
- **pthread_cond_t**: Las variables de condición (`condVarProd` y `condVarCons`) permiten a los hilos productores y consumidores suspender su ejecución hasta que la condición correspondiente (espacio disponible o productos disponibles) se cumpla.

## Notas
- El número de hilos productores y consumidores es controlado por la variable `max` (en este caso 4).
- Para probar el código, asegúrate de que tu entorno de desarrollo tenga soporte para la biblioteca POSIX threads.
