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