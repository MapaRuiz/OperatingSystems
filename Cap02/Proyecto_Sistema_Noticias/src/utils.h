#ifndef UTILS_H
#define UTILS_H

#define MAX_SUSCRIPTORES 100

int is_valid_news_format(const char *news) {
    // Validación del formato de las noticias.
    return (news && strlen(news) > 3 && news[1] == ':');
}

#endif
