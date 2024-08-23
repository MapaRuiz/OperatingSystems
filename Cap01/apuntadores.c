/*********************
Autor: Mapa Rodriguez
Materia: Sistemas operativos
Fecha: 1-08-24
Tema: Segunda parte de la introduccion al lenguaje C
 *********************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char *p = (char *)malloc(50 * sizeof(char)); // Asignar memoria para 50 caracteres
    char *q = (char *)malloc(10 * sizeof(char)); // Asignar memoria para 10 caracteres
    printf("Address of p = %p\n", (void *)p);
    
    strcpy(p, "Hello, I´m the best in Operating Systems!");
    printf("%s\n", p);
    
    printf("About to copy \"Goodbye\" to q\n");
    strcpy(q, "Goodbye");
    printf("String copied\n");
    printf("%s\n", q);

    free(p); // Liberar memoria asignada a p
    free(q); // Liberar memoria asignada a q
    
    return 0;
}
