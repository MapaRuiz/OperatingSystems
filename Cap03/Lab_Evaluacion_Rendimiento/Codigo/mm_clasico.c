/*********************
Autor: Mapa Rodriguez
Materia: Sistemas operativos
Fecha: 10-31-24
Tema: Taller de Evaluación de Rendimiento
Fichero: fuente de multiplicación de matrices NxN por hilos.
Objetivo: Evaluar el tiempo de ejecución del algoritmo clásico de multiplicación de matrices. Se implementa con la Biblioteca POSIX Pthreads
*********************/

#include <stdio.h>         // Biblioteca para entrada y salida estándar (printf)
#include <pthread.h>       // Biblioteca para manejo de hilos POSIX
#include <unistd.h>        // Biblioteca para funciones de UNIX (sleep, etc.)
#include <stdlib.h>        // Biblioteca estándar de C (malloc, atoi, srand, etc.)
#include <time.h>          // Biblioteca para manejo de tiempo (time)
#include <sys/time.h>      // Biblioteca para funciones de tiempo (gettimeofday)

#define DATA_SIZE (1024*1024*64*3) // Tamaño máximo del bloque de memoria para las matrices

pthread_mutex_t MM_mutex;       // Mutex para proteger secciones críticas (si las hubiera)
static double MEM_CHUNK[DATA_SIZE]; // Bloque de memoria estática para matrices
double *mA, *mB, *mC;           // Punteros para las matrices A, B y C

// Estructura para pasar parámetros a los hilos
struct parametros{
	int nH;   // Número total de hilos
	int idH;  // Identificador único del hilo actual
	int N;    // Dimensión de la matriz (NxN)
};

// Variables para medir el tiempo de ejecución
struct timeval start, stop;

// Llena las matrices mA y mB con valores iniciales y establece mC en cero
void llenar_matriz(int SZ){ 
	srand48(time(NULL));           // Inicializa el generador de números aleatorios
	for(int i = 0; i < SZ*SZ; i++){ // Itera sobre cada elemento en las matrices
			mA[i] = 1.1 * i;       // Asigna un valor secuencial a cada elemento de mA
			mB[i] = 2.2 * i;       // Asigna un valor secuencial a cada elemento de mB
			mC[i] = 0;             // Inicializa mC con ceros
		}	
}

// Imprime una matriz si su tamaño es menor a 12x12
void print_matrix(int sz, double *matriz){
	if(sz < 12){                   // Imprime solo si la matriz es menor de 12x12
    	for(int i = 0; i < sz*sz; i++){
     		if(i % sz == 0)        // Salto de línea al final de cada fila
				printf("\n");
            printf(" %.3f ", matriz[i]); // Imprime cada elemento con 3 decimales
		}	
    	printf("\n>-------------------->\n"); // Separador después de la impresión
	}
}

// Inicia la medición de tiempo
void inicial_tiempo(){
	gettimeofday(&start, NULL);    // Obtiene y guarda el tiempo inicial
}

// Finaliza la medición de tiempo e imprime la duración en microsegundos
void final_tiempo(){
	gettimeofday(&stop, NULL);     // Obtiene y guarda el tiempo final
	stop.tv_sec -= start.tv_sec;   // Calcula los segundos transcurridos
	printf("\n:-> %9.0f µs\n", (double)(stop.tv_sec*1000000 + stop.tv_usec)); // Imprime el tiempo en microsegundos
}

// Función que cada hilo ejecuta para multiplicar su porción de la matriz
void *mult_thread(void *variables){
	struct parametros *data = (struct parametros *)variables; // Convierte el argumento en un puntero a `parametros`
	
	int idH = data->idH;           // Identificador del hilo
	int nH  = data->nH;            // Número total de hilos
	int N   = data->N;             // Dimensión de la matriz (NxN)
	int ini = (N / nH) * idH;      // Índice de fila inicial para este hilo
	int fin = (N / nH) * (idH + 1); // Índice de fila final (exclusivo) para este hilo

    for (int i = ini; i < fin; i++){       // Recorre las filas asignadas al hilo
        for (int j = 0; j < N; j++){       // Recorre cada columna en la matriz
			double *pA, *pB, sumaTemp = 0.0; // Inicializa punteros y suma temporal
			pA = mA + (i * N);              // Puntero a la fila actual de mA
			pB = mB + j;                    // Puntero a la columna actual de mB
            for (int k = 0; k < N; k++, pA++, pB += N){ // Multiplica elementos y acumula
				sumaTemp += (*pA * *pB);    // Multiplicación acumulada en sumaTemp
			}
			mC[i * N + j] = sumaTemp;      // Asigna el valor calculado a la matriz resultante
		}
	}

	pthread_mutex_lock(&MM_mutex);         // Bloqueo del mutex (no es necesario en este caso)
	pthread_mutex_unlock(&MM_mutex);       // Desbloqueo del mutex (no es necesario en este caso)
	pthread_exit(NULL);                    // Termina el hilo
}

int main(int argc, char *argv[]){
	if (argc < 2){                     // Verifica si se han pasado suficientes argumentos
		printf("Ingreso de argumentos \n $./ejecutable tamMatriz numHilos\n");
		return -1;	
	}
    int SZ = atoi(argv[1]);            // Tamaño de la matriz (NxN)
    int n_threads = atoi(argv[2]);     // Número de hilos

    pthread_t p[n_threads];            // Arreglo de identificadores de hilos
    pthread_attr_t atrMM;              // Atributos para los hilos

	mA = MEM_CHUNK;                    // Asigna el bloque de memoria a mA
	mB = mA + SZ * SZ;                 // Asigna la memoria para mB después de mA
	mC = mB + SZ * SZ;                 // Asigna la memoria para mC después de mB

	llenar_matriz(SZ);                 // Llama a la función para inicializar las matrices
	print_matrix(SZ, mA);              // Imprime la matriz A
	print_matrix(SZ, mB);              // Imprime la matriz B

	inicial_tiempo();                  // Inicia la medición de tiempo
	pthread_mutex_init(&MM_mutex, NULL); // Inicializa el mutex
	pthread_attr_init(&atrMM);         // Inicializa los atributos de los hilos
	pthread_attr_setdetachstate(&atrMM, PTHREAD_CREATE_JOINABLE); // Configura los hilos como "joinable"

    for (int j = 0; j < n_threads; j++){ // Crea los hilos para la multiplicación
		struct parametros *datos = (struct parametros *) malloc(sizeof(struct parametros)); // Reserva memoria para los parámetros del hilo
		datos->idH = j;              // Establece el ID del hilo
		datos->nH  = n_threads;      // Establece el número total de hilos
		datos->N   = SZ;             // Establece el tamaño de la matriz
        pthread_create(&p[j], &atrMM, mult_thread, (void *)datos); // Crea el hilo con los parámetros asignados
	}

    for (int j = 0; j < n_threads; j++)  // Espera a que todos los hilos terminen
        pthread_join(p[j], NULL);
	final_tiempo();                    // Finaliza la medición de tiempo
	
	print_matrix(SZ, mC);              // Imprime la matriz resultante

	pthread_attr_destroy(&atrMM);      // Destruye los atributos de hilo
	pthread_mutex_destroy(&MM_mutex);  // Destruye el mutex
	pthread_exit(NULL);                // Finaliza el programa
}
