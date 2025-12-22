/* zadanie2.c */
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;

    int fd = open(argv[1], O_RDWR); // O_RDWR wymagane do odczytu i zapisu
    if (fd == -1) { perror("open"); return 1; }

    char ch;
    while (read(fd, &ch, 1) > 0) {
        if (ch == 'x') {
            lseek(fd, -1, SEEK_CUR); // Cofnij sie o 1 bajt
            write(fd, "X", 1);       // Nadpisz
        }
    }
    close(fd);
    return 0;
}