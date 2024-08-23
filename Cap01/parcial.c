/*********************
Autor: Mapa Rodriguez
Materia: Sistemas operativos
Fecha: 22-08-24
Tema: Parcial #1
 *********************/
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
static void resizeVector(vectorDinamico *V, int capacidad){
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

/*programa pricipal: crea un vector, lo inicializa, agrega dos elementos, los lee, los borra, asigna a una pos especifica, y los vuelve a leer*/
int main(){
        vectorDinamico editor;
        vectorInicio(&editor);
        
        addVector(&editor, "Hola");
        addVector(&editor, "Profesional");
        addVector(&editor, "en");
        addVector(&editor, "Formacion");
        addVector(&editor, "de");
        addVector(&editor, "Ingenieria");
        printf("\n \n");
        for (int i = 0; i < totalVector(&editor); i++)
                printf("%s ", (char *) getVector(&editor, i));

        printf("\n \n");
        borrarVector(&editor, 1);
        borrarVector(&editor, 4);
        borrarVector(&editor, 3);
        borrarVector(&editor, 2);
        setVector(&editor, 1, "Buenos");
        addVector(&editor, "Días");
        printf("\n \n");

        for (int i = 0; i < totalVector(&editor); i++)
                printf("%s ", (char *) getVector(&editor, i));
        printf("\n");

        freeVector(&editor);
}