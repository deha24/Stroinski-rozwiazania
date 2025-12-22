/* zadanie5b.c */
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        int fd = open(argv[i], O_RDONLY);
        if (fd == -1) {
            perror(argv[i]);
            continue;
        }
        off_t size = lseek(fd, 0, SEEK_END);
        printf("Plik: %s, Rozmiar: %ld bytow\n", argv[i], size);
        close(fd);
    }
    return 0;
}/* zadanie5b.c */
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        int fd = open(argv[i], O_RDONLY);
        if (fd == -1) {
            perror(argv[i]);
            continue;
        }
        off_t size = lseek(fd, 0, SEEK_END);
        printf("Plik: %s, Rozmiar: %ld bytow\n", argv[i], size);
        close(fd);
    }
    return 0;
}