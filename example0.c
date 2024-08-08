/*********************
Autor: Mapa Rodriguez
Materia: Sistemas operativos
Fecha: 18-07-24
Tema: Introduccion al lenguaje C y los entornos
 -Entornos en la web (Cloud/Nube)
 -Comandos principales de Linux
 -Programa 0: hola mundo
 *********************/

#include <stdio.h>
#include <stdlib.h>

#define AZUL_T     "\x1b[34m"
#define ROJO_T     "\x1b[31m"

int main(int argc, char *argv[]){
  
  printf(ROJO_T"--------------------------- \n");
  printf(AZUL_T"  NOMBRE: Mapa Rodriguez Ruiz \n");
  printf("  CANTIDAD: 6 Materias \n");
  printf("  CARRERA: Ingenieria de sistemas \n");
  printf(ROJO_T"--------------------------- \n");
  
  return 0;
}
