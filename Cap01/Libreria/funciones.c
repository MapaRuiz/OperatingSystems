/*********************
Autor: Mapa Rodriguez
Materia: Sistemas operativos
Fecha: 25-07-24
Tema: Entrada y salida en C
 *********************/

#include <stdio.h>
#include <math.h>
#include "funciones.h"

#ifndef MPI
#define MPI 3.14159265358979323846
#endif

void sumarEnteros(){
      /*sumar dos valores que entran por teclado*/
      int a, b;
      printf("Ingrese el primer valor \n");
      scanf("%d", &a);
      printf("Ingrese el segundo valor \n");
      scanf("%d", &b);

      double suma = a + b;
      printf("la suma de %d + %d = %f \n", a, b, suma);
}
void areaCirculo(){
      /*calcular el area de circulo ingreso por teclado radio*/
      int r1;
      printf("Ingrese radio del circulo \n");
      scanf("%d", &r1);

      double area = MPI * (pow(r1,2));
      printf("El area del circulo es = %f \n", area);
}
void volumenCircunferencia(){
      /*calcular el volumen de circunferencia ingreso por teclado radio*/
      int r2;
      printf("Ingrese radio del circulo \n");
      scanf("%d", &r2);

      double vcircunferencia = (4 * MPI * (pow(r2,3))) / 3;

      printf("El volumen de la circunferencia es = %f \n", vcircunferencia);
}
void volumenCono(){
      /*calcular el volumen de un cono ingreso por teclado variables necesarias*/
      int r3;
      printf("Ingrese el radio del cono \n");
      scanf("%d", &r3);

      int altura;
      printf("Ingrese la altura del cono \n");
      scanf("%d", &altura);

      double vcono = (MPI * (pow(r3,2)) * altura) / 3;

      printf("El volumen del cono es = %f \n", vcono);
}
void calcHipo(){
      /*calcular hipotenusa ingreso por teclado variables necesarias*/
      int copuesto;
      printf("Ingrese cateto opuesto \n");
      scanf("%d", &copuesto);

      int cadyacente;
      printf("Ingrese cateto adyacente \n");
      scanf("%d", &cadyacente);

      double calc = (pow(copuesto,2)) + (pow(cadyacente,2));
      double hipo = sqrt(calc);

      printf("La hipotenusa es = %f \n", hipo);
}