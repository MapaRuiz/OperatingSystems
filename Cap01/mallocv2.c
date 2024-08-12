/*********************
Autor: Mapa Rodriguez
Materia: Sistemas operativos
Fecha: 08-08-24
Tema: Asignación de memoria dinámica
      Asignación de memoria en Bytes de almacenamiento
 *********************/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {

  int *varptr1 = malloc(4*sizeof(int)); //Asignacion suficiente para un vector entero de size 4
  int *varptr2 = malloc(sizeof(int[4])); //Asignacion suficiente para un vector entero de size 4
  int *varptr3 = malloc(4*sizeof(*varptr3)); //Asignacion suficiente para un vector entero de size 4

  if(varptr1){
    for(int i=0; i<4; i++){
      varptr1[i] = i*i;
    }
    for(int i=0; i<4; i++){
      printf("varptr1[%d] \t == %d\n",i, varptr1[i]);
    }
  }

  printf("Se libera memoria reservada \n");
  free(varptr1);
  free(varptr2);
  free(varptr3);

  return 0;
}