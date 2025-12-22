/* zadanie5a.c */
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) return 1;

    char ch;
    int current_len = 0, max_len = 0;

    while (read(fd, &ch, 1) > 0) {
        if (ch == '\n') {
            if (current_len > max_len) max_len = current_len;
            current_len = 0;
        } else {
            current_len++;
        }
    }
    // Sprawdz ostatnia linie jesli nie ma entera na koncu
    if (current_len > max_len) max_len = current_len;

    printf("Najdluzsza linia ma: %d znakow\n", max_len);
    close(fd);
    return 0;
}