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

  char a [25] = "Mapa Rodriguez Ruiz";
  int b = 6;
  char c [25] = "Ingenieria de sistemas";

  printf(ROJO_T"--------------------------- \n");
  printf(AZUL_T"  NOMBRE: %s \n", a);
  printf("  CANTIDAD: %d Materias \n", b);
  printf("  CARRERA: %s \n", c);
  printf(ROJO_T"--------------------------- \n");

  return 0;
}