/* zadanie4.c */
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) { perror("open"); return 1; }

    // Ustaw na koniec pliku i pobierz rozmiar
    off_t size = lseek(fd, 0, SEEK_END);
    char ch;

    // Czytaj znak po znaku od konca
    for (off_t i = 1; i <= size; i++) {
        lseek(fd, -i, SEEK_END);
        read(fd, &ch, 1);
        write(1, &ch, 1); // 1 to STDOUT
    }
    write(1, "\n", 1);
    close(fd);
    return 0;
}