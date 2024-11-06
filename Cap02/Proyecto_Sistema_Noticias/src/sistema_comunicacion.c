#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/select.h>
#include <time.h>

#define BUFFER_SIZE 1024
#define MAX_SUSCRIPTORES 100
#define MAX_NOTICIAS 100

typedef struct {
    char tipo;                    // Topic (e.g., 'A', 'E')
    char contenido[BUFFER_SIZE];  // News description
} Noticia;

typedef struct {
    char topics[BUFFER_SIZE];     // Topics subscriber is interested in (e.g., "A E")
    char pipe_name[BUFFER_SIZE];  // Subscriber's unique pipe
} Suscriptor;

Suscriptor suscriptores[MAX_SUSCRIPTORES];
Noticia noticias[MAX_NOTICIAS];
int num_suscriptores = 0;
int num_noticias = 0;
time_t last_news_time;  // Track the last news timestamp

void almacenar_noticia(const char *noticia_text) {
    if (num_noticias >= MAX_NOTICIAS) {
        fprintf(stderr, "News storage is full, cannot store more news.\n");
        return;
    }
    noticias[num_noticias].tipo = noticia_text[0];  // Topic is the first character
    strncpy(noticias[num_noticias].contenido, noticia_text, BUFFER_SIZE);
    num_noticias++;
    last_news_time = time(NULL);  // Update last news time
}

void enviar_noticia_a_suscriptor(const Suscriptor *suscriptor, const Noticia *noticia) {
    if (strchr(suscriptor->topics, noticia->tipo)) {  // Check if topic matches
        int fd = open(suscriptor->pipe_name, O_WRONLY | O_NONBLOCK);
        if (fd != -1) {
            write(fd, noticia->contenido, strlen(noticia->contenido));
            close(fd);
        } else {
            perror("Error opening subscriber pipe");
        }
    }
}

void registrar_suscriptor(const char *message) {
    if (num_suscriptores >= MAX_SUSCRIPTORES) {
        fprintf(stderr, "Max subscribers reached.\n");
        return;
    }
    char *delimiter = strchr(message, ':');
    if (!delimiter) return;
    *delimiter = '\0';
    strncpy(suscriptores[num_suscriptores].pipe_name, message, BUFFER_SIZE);
    // Normalize topics to remove spaces for easier matching
    char *topics = delimiter + 1;
    for (int i = 0, j = 0; topics[i] != '\0'; i++) {
        if (topics[i] != ' ') {
            suscriptores[num_suscriptores].topics[j++] = topics[i];
        }
    }
    printf("Subscriber registered: Pipe=%s Topics=%s\n",
           suscriptores[num_suscriptores].pipe_name,
           suscriptores[num_suscriptores].topics);

    // Send all relevant news to the new subscriber
    for (int i = 0; i < num_noticias; i++) {
        enviar_noticia_a_suscriptor(&suscriptores[num_suscriptores], &noticias[i]);
    }

    num_suscriptores++;
}

void finalizar_transmision() {
    const char *end_message = "End of news broadcast.\n";
    printf("No new publishers detected. Broadcasting end of transmission.\n");
    for (int i = 0; i < num_suscriptores; i++) {
        int fd = open(suscriptores[i].pipe_name, O_WRONLY | O_NONBLOCK);
        if (fd != -1) {
            write(fd, end_message, strlen(end_message));
            close(fd);
        } else {
            perror("Error opening subscriber pipe for final message");
        }
    }
}

int main(int argc, char *argv[]) {
    char *pipePSC = NULL, *pipeSSC = NULL;
    int timeF = 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
            pipePSC = argv[++i];
        } else if (strcmp(argv[i], "-s") == 0 && i + 1 < argc) {
            pipeSSC = argv[++i];
        } else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc) {
            timeF = atoi(argv[++i]);
        }
    }
    if (!pipePSC || !pipeSSC || timeF <= 0) {
        fprintf(stderr, "Usage: sistema -p pipePSC -s pipeSSC -t timeF\n");
        exit(EXIT_FAILURE);
    }

    mkfifo(pipePSC, 0666);
    mkfifo(pipeSSC, 0666);

    int fdPSC = open(pipePSC, O_RDONLY | O_NONBLOCK);  // Open `pipePSC` non-blocking
    int fdSSC = open(pipeSSC, O_RDONLY | O_NONBLOCK);

    if (fdPSC == -1 || fdSSC == -1) {
        perror("Error opening pipes");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    fd_set read_fds;
    int max_fd = (fdPSC > fdSSC ? fdPSC : fdSSC) + 1;

    last_news_time = time(NULL);
    printf(">>> SYSTEM STARTED <<<\n");

    while (1) {
        FD_ZERO(&read_fds);
        FD_SET(fdPSC, &read_fds);
        FD_SET(fdSSC, &read_fds);

        struct timeval timeout;
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        if (select(max_fd, &read_fds, NULL, NULL, &timeout) > 0) {
            if (FD_ISSET(fdPSC, &read_fds)) {
                int bytes_read = read(fdPSC, buffer, sizeof(buffer) - 1);
                if (bytes_read > 0) {
                    buffer[bytes_read] = '\0';
                    printf("News received from publisher: %s\n", buffer);
                    last_news_time = time(NULL);
                    almacenar_noticia(buffer);  // Store the news

                    // Distribute news to all subscribers
                    for (int i = 0; i < num_suscriptores; i++) {
                        enviar_noticia_a_suscriptor(&suscriptores[i], &noticias[num_noticias - 1]);
                    }
                }
            }
            if (FD_ISSET(fdSSC, &read_fds)) {
                int bytes_read = read(fdSSC, buffer, sizeof(buffer) - 1);
                if (bytes_read > 0) {
                    buffer[bytes_read] = '\0';
                    registrar_suscriptor(buffer);  // Register subscriber and send relevant news
                }
            }
        }

        // Only check for inactivity on `pipePSC` (publisher pipe)
        if (difftime(time(NULL), last_news_time) >= timeF) {
            finalizar_transmision();
            break;
        }
    }

    close(fdPSC);
    close(fdSSC);
    unlink(pipePSC);
    unlink(pipeSSC);
    return 0;
}
