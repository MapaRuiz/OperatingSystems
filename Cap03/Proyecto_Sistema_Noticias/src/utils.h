#ifndef UTILS_H
#define UTILS_H

#include <string.h> // Incluye funciones para manipulación de cadenas

#define MAX_SUSCRIPTORES 100

// Función que valida el formato de las noticias.
int is_valid_news_format(const char *news) {
    // Verifica que la noticia no sea NULL, tenga longitud suficiente,
    // comience con uno de los caracteres válidos y el segundo carácter sea ':'
    return (news && strlen(news) > 3 && 
            (news[0] == 'A' || news[0] == 'E' || news[0] == 'C' || news[0] == 'P' || news[0] == 'S') &&
            news[1] == ':');
}

#endif
