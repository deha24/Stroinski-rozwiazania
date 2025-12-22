/* zadanie9.c */
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int fd = 0; // Domyslnie STDIN (deskryptor 0)

    if (argc > 1) {
        fd = open(argv[1], O_RDONLY);
        if (fd == -1) { perror("open"); return 1; }
    }

    char buf[1];
    while (read(fd, buf, 1) > 0) {
        buf[0] = toupper(buf[0]);
        write(1, buf, 1); // Wypisz na STDOUT (deskryptor 1)
    }

    if (fd != 0) close(fd);
    return 0;
}