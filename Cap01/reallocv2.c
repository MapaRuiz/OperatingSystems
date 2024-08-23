/*********************
Autor: Mapa Rodriguez
Materia: Sistemas operativos
Fecha: 08-08-24
Tema: Asignación de memoria dinámica
      Asignación de memoria en Bytes de almacenamiento
 *********************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*Funcion para imprimir el tamano reasignado*/
void Info_Almacenamiento(const int *siguiente, const int*anterior, int valores){
  if(siguiente){
    printf("%s ubicacion = %p. Tamano reservado: %d valores (%ld bytes). \n", 
           (siguiente != anterior ? "Nuevo" : "Anterior"), (void*)siguiente, valores, valores *sizeof(int));
  }

}

int main(int argc, char * argv[]) {

  const int patron[] = {1,2,3,4,5,6,7,8};
  const int patron_size = sizeof(patron)/sizeof(int);
  int *siguiente = NULL, *anterior = NULL;

  siguiente = (int *)malloc(patron_size * sizeof(*siguiente)); // Asigna el vector
  if(siguiente){
    memcpy(siguiente, patron, sizeof(patron)); //llena el vector
    Info_Almacenamiento(siguiente, anterior, patron_size);
  }else{
    return EXIT_FAILURE;
  }
  //Reasigna los valores del vector en el siguiente ciclo
  const int realloc_size[]= {10,20,30,40,50,60,70,80};
      
  for(int i =0; i!= (sizeof(realloc_size)/sizeof(int)); i++){
    anterior = siguiente; // Guarda la dirección anterior
    siguiente = (int *)realloc(siguiente, realloc_size[i] * sizeof(int)); // Reasigna la memoria
    
    if(siguiente){
      Info_Almacenamiento(siguiente, anterior, realloc_size[i]);
      assert(!memcmp(siguiente, patron, sizeof(patron)));
    }
    else {
      // Si realloc falla, libera la memoria y sale del programa
      free(anterior);
      return EXIT_FAILURE;
    }
    
  }

  printf("Se libera memoria reservada \n");

  free(siguiente);

  return 0;
}
