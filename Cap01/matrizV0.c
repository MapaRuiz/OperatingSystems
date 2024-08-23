/*********************
Autor: Mapa Rodriguez
Materia: Sistemas operativos
Fecha: 15-08-24
Tema: Gestion de memoria
      - Diferencias entre usar o no usar Punteros
 *********************/
#include <stdio.h>
#include <stdlib.h>

// Impresión de matrices
void impresionMatriz(int size, int* matriz, int salto) {
    if(size < 6) {     
        for(int i = 0; i < size; i++) {
            if(i % salto == 0) {
                printf("\n");
            }
            printf(" %d ", *(matriz + i));
        }
        printf("\n");
    }
}

// Inicialización
void inicializacion(int size, int* mA, int* mB, int* mC) {
    for(int i = 0; i < size; i++) {
        *(mA + i) = 1;
        *(mB + i) = 2;
        *(mC + i) = 0;
    }
}

// Multiplicación de matrices
void multiplicacionMatrices(int n, int* mA, int* mB, int* mC) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int suma = 0;
            for(int k = 0; k < n; k++) {
                suma += *(mA + i * n + k) * *(mB + k * n + j);
            }
            *(mC + i * n + j) = suma;
        }
    }
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("Usage: %s tamanoFilaMatriz \n", argv[0]);
        exit(0);
    }

    int n = atoi(argv[1]);
    int size = n * n;
    int* mA = (int*)malloc(size * sizeof(int));
    int* mB = (int*)malloc(size * sizeof(int));
    int* mC = (int*)malloc(size * sizeof(int));

    if (mA == NULL || mB == NULL || mC == NULL) {
        printf("Error al asignar memoria.\n");
        exit(1);
    }

    inicializacion(size, mA, mB, mC);

    // Impresión de mA
    impresionMatriz(size, mA, n);
    // Impresión de mB
    impresionMatriz(size, mB, n);

    // Multiplicación de matrices mAxmB = mC
    multiplicacionMatrices(n, mA, mB, mC);

    // Impresión de mC
    impresionMatriz(size, mC, n);

    // Liberar memoria
    free(mA);
    free(mB);
    free(mC);

    printf("\n\n\n. . .Fin del programa =) \n");
    return 0;
}
