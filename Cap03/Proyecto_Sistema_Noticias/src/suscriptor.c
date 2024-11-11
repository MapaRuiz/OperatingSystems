#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    char *pipeSSC = NULL;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-s") == 0 && i + 1 < argc) {
            pipeSSC = argv[++i];
        }
    }
    if (!pipeSSC) {
        fprintf(stderr, "Usage: suscriptor -s pipeSSC\n");
        exit(EXIT_FAILURE);
    }

    // Generate a unique path in /tmp for the subscriber pipe
    char pipeUnique[BUFFER_SIZE];
    snprintf(pipeUnique, sizeof(pipeUnique), "/tmp/pipeS_%d", getpid());
    if (mkfifo(pipeUnique, 0666) == -1 && errno != EEXIST) {
        perror("Error creating unique pipe in /tmp");
        exit(EXIT_FAILURE);
    }

    // Open the shared pipe to send subscription topics and unique pipe name
    int fd_shared = open(pipeSSC, O_WRONLY);
    if (fd_shared == -1) {
        unlink(pipeUnique);
        perror("Error opening shared pipe for topics");
        exit(EXIT_FAILURE);
    }

    // Get topics of interest from user
    char topics[BUFFER_SIZE];
    printf("Enter topics of interest (e.g., A E S): ");
    fgets(topics, sizeof(topics), stdin);
    topics[strcspn(topics, "\n")] = '\0';  // Remove newline character

    // Send subscription data in format "pipeUnique:topics"
    dprintf(fd_shared, "%s:%s\n", pipeUnique, topics);
    close(fd_shared);

    // Open the unique pipe to receive news in blocking mode
    int fd = open(pipeUnique, O_RDONLY);
    if (fd == -1) {
        unlink(pipeUnique);
        perror("Error opening unique pipe for reading news");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for news on selected topics...\n");
    char buffer[BUFFER_SIZE];

    // Keep reading news until the "End of news broadcast" message is received
    while (1) {
        int bytesRead = read(fd, buffer, sizeof(buffer) - 1);
        if (bytesRead > 0) {
            buffer[bytesRead] = '\0';

            // Check for the end of broadcast message
            if (strcmp(buffer, "End of news broadcast.\n") == 0) {
                printf("%s", buffer);  // Display the end message
                break;                 // Exit after receiving the end message
            }

            printf("Received news: %s\n", buffer);  // Display regular news
        } else if (bytesRead < 0){
            perror("Error reading from unique pipe");
            break;
        }
    }

    close(fd);
    unlink(pipeUnique);  // Clean up unique pipe after finishing
    return 0;
}
