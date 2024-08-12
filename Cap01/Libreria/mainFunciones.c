/*********************
Autor: Mapa Rodriguez
Materia: Sistemas operativos
Fecha: 25-07-24
Tema: Entrada y salida en C
 *********************/

#include <stdio.h>
#include <math.h>
#include "funciones.h"

int main(int argc, char *argv[]){
  int op;
  printf("--------------------------- \n");
  printf("CALCULADORA \n");
  printf("--------------------------- \n");
  printf("1. Suma dos valores \n");
  printf("2. Area circulo \n");
  printf("3. Volumen circunferencia \n");
  printf("4. Volumen cono \n");
  printf("5. Calcular hipotenusa \n");
  printf("0. Salir \n");
  printf("--------------------------- \n");

  do{
  printf("Ingrese la opcion \n");
  scanf("%d", &op);
  
  switch(op){
    case 0:
      printf("Saliendo del programa \n");
    break;
    case 1:
      printf("SUMA DOS VALORES \n");
      sumarEnteros();
    break;
    case 2:
      printf("AREA DEL CIRCULO \n");
      areaCirculo();
    break;
    case 3:
      printf("VOLUMEN DE UNA CIRCUNFERENCIA \n");
      volumenCircunferencia();
    break;
    case 4:
      printf("VOLUMEN DE UN CONO \n");
      volumenCono();
    break;
    case 5:
      printf("CALCULAR HIPOTENUSA \n");
      calcHipo();
    break;
    default:
      printf("OPCION NO VALIDA \n"); 
  }
  }while(op != 0);

  return 0;
}