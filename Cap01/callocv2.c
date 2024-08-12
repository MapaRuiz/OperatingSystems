/*********************
Autor: Mapa Rodriguez
Materia: Sistemas operativos
Fecha: 08-08-24
Tema: Asignación de memoria dinámica
      Asignación de memoria en Bytes de almacenamiento
 *********************/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int *vP1 = calloc(4,sizeof(int)); //Asignacion para un vector INT de size 4, inicializa en 0
  int *vP2 = calloc(1, sizeof(int[4])); //Asignacion para un vector INT de size 4, inicializa en 0
  int *vP3 = calloc(4,sizeof(*vP3)); //Asignacion para un vector INT de size 4, inicializa en 0

  if(vP2) {    
    for(int i = 0; i < 4; i++) {
      printf("vP2[%d]\t == %d\n", i, vP2[i]);
    }
  }

  printf("Se liberara la memoria reservada\n");
  free(vP1);
  free(vP2);
  free(vP3);

  return 0;
}