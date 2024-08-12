/*********************
Autor: Mapa Rodriguez
Materia: Sistemas operativos
Fecha: 1-08-24
Tema: Segunda parte de la introduccion al lenguaje C
 *********************/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  int variable = 123;
  int *ptr = &variable;
  
  printf("Valor de la variable: %d\n", variable);
  printf("Dirección de memoria de la variable: %p\n", &variable);
  printf("Dirección a la que apunta el puntero: %p\n", (void *)ptr);
  printf("Valor de la variable: %i\n", *ptr);
  
  return 0;
}