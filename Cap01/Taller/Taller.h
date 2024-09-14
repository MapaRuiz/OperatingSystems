/*********************
Autor: Mapa Rodriguez
Materia: Sistemas operativos
Fecha: 29-08-24
Tema: Laboratorio de compilacion modular
- Funcionamiento del codigo
- Modularizacion del codigo
- Creacion de fichero de automatizacion de compilacion
 *********************/
#ifndef __TALLER_H__
#define __TALLER_H__


#include <stdlib.h>
#include <stdio.h>
#define CAPACIDAD_INICIAL 4

/*Creación Estructura de Datos para el Vector*/
typedef struct vectorDinamico{
        int capacidad;
        int totalElementos;
        void **elementos;
} vectorDinamico;

/*Inicializar el Vector*/
void vectorInicio(vectorDinamico *V);

/*Calcular y retornar el total de elementos*/
int totalVector(vectorDinamico *V);

/*Modificar el tamano del vector*/
void resizeVector(vectorDinamico *V, int capacidad);

/*Agregar un elemento reajustando el tamano de ser necesario*/
void addVector(vectorDinamico *V, void *elemento);

/*Liberar la memoria que ocupa el vector*/
void freeVector(vectorDinamico *V);

/*Buscar un elemento en todo el vector y retornar su valor de encontrarlo*/
void *getVector(vectorDinamico *V, int indice);

/*agregar un elemento a una posicion especifica del vector*/
void setVector(vectorDinamico *V, int indice, void *elemento);

/*Eliminar una posicion especifica del vector y mover todos los de la derecha a esta para no tener un espacio vacio*/
void borrarVector(vectorDinamico *V, int indice);

#endif