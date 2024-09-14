/*********************
Autor: Mapa Rodriguez
Materia: Sistemas operativos
Fecha: 29-08-24
Tema: Laboratorio de compilacion modular
- Funcionamiento del codigo
- Modularizacion del codigo
- Creacion de fichero de automatizacion de compilacion
 *********************/
#include <stdlib.h>
#include <stdio.h>
#include "Taller.h"

/*Inicializar el Vector*/
void vectorInicio(vectorDinamico *V){
        V->capacidad = CAPACIDAD_INICIAL;
        V->totalElementos = 0;
        V->elementos = malloc(sizeof(void *) * V->capacidad); 
}

/*Calcular y retornar el total de elementos*/
int totalVector(vectorDinamico *V){
        return V->totalElementos;
}

/*Modificar el tamano del vector*/
void resizeVector(vectorDinamico *V, int capacidad){
        printf("Redimensión: %d a %d \n", V->capacidad, capacidad);

        void **elementos = realloc(V->elementos, sizeof(void *) * capacidad);
        if(elementos){
                V->elementos = elementos;
                V->capacidad = capacidad;
        }
}

/*Agregar un elemento reajustando el tamano de ser necesario*/
void addVector(vectorDinamico *V, void *elemento){
        if(V->capacidad == V->totalElementos)
                resizeVector(V, V->capacidad*2);
        V->elementos[V->totalElementos++] = elemento;
}

/*Liberar la memoria que ocupa el vector*/
void freeVector(vectorDinamico *V){
        free(V->elementos);
}

/*Buscar un elemento en todo el vector y retornar su valor de encontrarlo*/
void *getVector(vectorDinamico *V, int indice){
        if(indice >= 0 && indice < V->totalElementos)
                return V->elementos[indice];
        return NULL;
}

/*agregar un elemento a una posicion especifica del vector*/
void setVector(vectorDinamico *V, int indice, void *elemento){
        if(indice >= 0 && indice < V->totalElementos)
                V->elementos[indice]=elemento;
}

/*Eliminar una posicion especifica del vector y mover todos los de la derecha a esta para no tener un espacio vacio*/
void borrarVector(vectorDinamico *V, int indice){
        if(indice < 0 || indice >= V->totalElementos)
                return; 

        V->elementos[indice] = NULL;

        for(int i=indice; i<V->totalElementos-1; i++){
                V->elementos[i] = V->elementos[i+1];
                V->elementos[i+1] = NULL; 
        }
        V->totalElementos--;
        if(V->totalElementos>0 && V->totalElementos == V->capacidad/4)
                resizeVector(V, V->capacidad/2);
}