/* zadanie1.c */
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        dprintf(2, "Uzycie: %s <plik> <tekst>\n", argv[0]);
        return 1;
    }

    // O_CREAT | O_TRUNC - utworz lub wyczysc, O_WRONLY - tylko zapis
    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) { perror("open"); return 1; }

    write(fd, argv[2], strlen(argv[2]));
    close(fd);
    return 0;
}