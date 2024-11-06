#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "utils.h"

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    char *pipePSC = NULL;
    char *filename = NULL;
    int timeN = 1;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
            pipePSC = argv[++i];
        } else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            filename = argv[++i];
        } else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc) {
            timeN = atoi(argv[++i]);
        }
    }

    if (!pipePSC || !filename) {
        fprintf(stderr, "Usage: publicador -p pipePSC -f file -t timeN\n");
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening news file");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    while (fgets(buffer, sizeof(buffer), file)) {
        if (is_valid_news_format(buffer)) {
            // Open, write one news item, then close pipePSC
            int fd = open(pipePSC, O_WRONLY | O_NONBLOCK);
            if (fd == -1) {
                perror("Error opening pipePSC");
                fclose(file);
                exit(EXIT_FAILURE);
            }
            write(fd, buffer, strlen(buffer));
            close(fd);  // Close the pipe to allow `sistema` to process each item

            printf("Noticia enviada: %s", buffer);
            sleep(timeN);  // Wait timeN seconds before sending the next news item
        } else {
            fprintf(stderr, "Invalid news format: %s", buffer);
        }
    }

    fclose(file);
    return 0;
}
