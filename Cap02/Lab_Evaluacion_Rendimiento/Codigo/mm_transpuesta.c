/*********************
Autor: Mapa Rodriguez
Materia: Sistemas operativos
Fecha: 10-31-24
Tema: Taller de Evaluación de Rendimiento
Fichero: fuente de multiplicación de matrices NxN por hilos.
Objetivo: Evaluar el tiempo de ejecución del algoritmo clásico de multiplicación de matrices. Se implementa con la Biblioteca POSIX Pthreads
*********************/

#include <stdio.h>         // Biblioteca para funciones de entrada y salida estándar
#include <pthread.h>       // Biblioteca para manejar hilos con POSIX
#include <unistd.h>        // Biblioteca para funciones UNIX estándar (sleep, etc.)
#include <stdlib.h>        // Biblioteca estándar de C (malloc, atoi, etc.)
#include <time.h>          // Biblioteca para manejar tiempo
#include <sys/time.h>      // Biblioteca para funciones de tiempo (gettimeofday)

// Define el tamaño del bloque de memoria para almacenar matrices
#define DATA_SIZE (1024*1024*64*3) 

pthread_mutex_t MM_mutex;  // Mutex para proteger secciones críticas en el código
static double MEM_CHUNK[DATA_SIZE]; // Bloque de memoria compartido para matrices
double *mA, *mB, *mC;      // Punteros para las matrices A, B y C

// Estructura para los parámetros que se pasarán a cada hilo
struct parametros{
	int nH;   // Número total de hilos
	int idH;  // Identificador del hilo actual
	int N;    // Dimensión de la matriz (NxN)
};

// Variables globales para medir el tiempo de ejecución
struct timeval start, stop;

// Función que llena las matrices mA y mB con valores secuenciales, y mC con ceros
void llenar_matriz(int SZ){ 
	srand48(time(NULL));            // Inicializa el generador de números aleatorios
	for(int i = 0; i < SZ*SZ; i++){ // Recorre cada elemento de las matrices
		mA[i] = 1.1 * i;           // Asigna un valor secuencial a cada elemento de mA
		mB[i] = 2.2 * i;           // Asigna un valor secuencial a cada elemento de mB
		mC[i] = 0;                 // Inicializa mC en cero
	}	
}

// Función que imprime la matriz en la consola si su tamaño es menor a 12x12
void print_matrix(int sz, double *matriz){
	if(sz < 12){                   // Condición para matrices pequeñas
		for(int i = 0; i < sz*sz; i++){ // Recorre todos los elementos de la matriz
			if(i % sz == 0) printf("\n"); // Salto de línea al final de cada fila
			printf(" %.3f ", matriz[i]); // Imprime cada elemento con 3 decimales
		}	
    	printf("\n>-------------------->\n"); // Separador al final de la impresión
	}
}

// Inicia la medición de tiempo de ejecución
void inicial_tiempo(){
	gettimeofday(&start, NULL);    // Obtiene el tiempo actual y lo almacena en `start`
}

// Finaliza la medición de tiempo e imprime la duración en microsegundos
void final_tiempo(){
	gettimeofday(&stop, NULL);     // Obtiene el tiempo actual y lo almacena en `stop`
	stop.tv_sec -= start.tv_sec;   // Resta los segundos iniciales a los finales
	printf("\n:-> %9.0f µs\n", (double) (stop.tv_sec * 1000000 + stop.tv_usec)); // Imprime el tiempo total en microsegundos
}

// Función que realiza la multiplicación de matrices en paralelo
void *mult_thread(void *variables){
	struct parametros *data = (struct parametros *)variables; // Convierte el argumento en un puntero a `parametros`
	
	int idH = data->idH;           // Identificador del hilo actual
	int nH  = data->nH;            // Número total de hilos
	int N   = data->N;             // Dimensión de la matriz (NxN)
	int ini = (N / nH) * idH;      // Índice de fila inicial asignado a este hilo
	int fin = (N / nH) * (idH + 1); // Índice de fila final (exclusivo) para este hilo

    for (int i = ini; i < fin; i++){ // Recorre las filas asignadas al hilo
        for (int j = 0; j < N; j++){ // Recorre cada columna de la matriz
			double *pA, *pB, sumaTemp = 0.0; // Punteros y acumulador de la suma temporal
			pA = mA + (i * N);               // Puntero a la fila actual de mA
			pB = mB + (j * N);               // Puntero a la columna actual de mB
            for (int k = 0; k < N; k++, pA++, pB++){ // Realiza la multiplicación y acumula
				sumaTemp += (*pA * *pB);     // Multiplica y suma al acumulador
			}
			mC[i * N + j] = sumaTemp;       // Asigna el resultado en la matriz C
		}
	}

	pthread_mutex_lock(&MM_mutex);          // Bloqueo del mutex (sin efecto en este contexto)
	pthread_mutex_unlock(&MM_mutex);        // Desbloqueo del mutex
	pthread_exit(NULL);                     // Termina el hilo
}

int main(int argc, char *argv[]){
	if (argc < 2){                        // Verifica si se han pasado suficientes argumentos
		printf("Ingreso de argumentos \n $./ejecutable tamMatriz numHilos\n");
		return -1;	
	}
    int SZ = atoi(argv[1]);               // Tamaño de la matriz (NxN)
    int n_threads = atoi(argv[2]);        // Número de hilos

    pthread_t p[n_threads];               // Arreglo de identificadores de hilos
    pthread_attr_t atrMM;                 // Atributos para los hilos

	mA = MEM_CHUNK;                       // Apunta mA al inicio del bloque de memoria
	mB = mA + SZ * SZ;                    // Coloca mB después de mA en el bloque de memoria
	mC = mB + SZ * SZ;                    // Coloca mC después de mB en el bloque de memoria

	llenar_matriz(SZ);                    // Llama a la función para llenar las matrices
	print_matrix(SZ, mA);                 // Imprime la matriz A (si es pequeña)
	print_matrix(SZ, mB);                 // Imprime la matriz B (si es pequeña)

	inicial_tiempo();                     // Inicia la medición de tiempo
	pthread_mutex_init(&MM_mutex, NULL);  // Inicializa el mutex
	pthread_attr_init(&atrMM);            // Inicializa los atributos de los hilos
	pthread_attr_setdetachstate(&atrMM, PTHREAD_CREATE_JOINABLE); // Configura los hilos como "joinable"

    for (int j = 0; j < n_threads; j++){  // Crea y lanza los hilos para la multiplicación
		struct parametros *datos = (struct parametros *) malloc(sizeof(struct parametros)); // Reserva memoria para los parámetros de cada hilo
		datos->idH = j;                  // Asigna el ID del hilo
		datos->nH  = n_threads;          // Asigna el número total de hilos
		datos->N   = SZ;                 // Asigna el tamaño de la matriz
        pthread_create(&p[j], &atrMM, mult_thread, (void *)datos); // Crea el hilo con los parámetros asignados
	}

    for (int j = 0; j < n_threads; j++)   // Espera a que todos los hilos terminen
        pthread_join(p[j], NULL);         
	final_tiempo();                       // Finaliza la medición de tiempo
	
	print_matrix(SZ, mC);                 // Imprime la matriz resultante C

	pthread_attr_destroy(&atrMM);         // Libera los recursos de los atributos de hilos
	pthread_mutex_destroy(&MM_mutex);     // Libera los recursos del mutex
	pthread_exit(NULL);                   // Termina el programa
}
