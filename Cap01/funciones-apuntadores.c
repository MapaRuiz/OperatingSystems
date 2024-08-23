/*********************
Autor: Mapa Rodriguez
Materia: Sistemas operativos
Fecha: 1-08-24
Tema: Segunda parte de la introduccion al lenguaje C
 *********************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *function(char *p);

int main(){
  char *a = NULL;
  char *b = NULL;
  
  a = function("Hi, it's fun to learn");
  
  b = function("Systems engineering");
  
  printf("From main: %s %s\n", a, b);
}

char * function(char *p){
  
  char *q = (char *)malloc(strlen(p) + 1);
  
  strcpy(q, p);
  
  printf(" From q: the string is %s\n", q);
  
  return q;
}
