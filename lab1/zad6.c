/* zadanie6b.c - wypisz liniami od końca */
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) return 1;

    off_t pos = lseek(fd, 0, SEEK_END);
    off_t end_line = pos;

    while (pos > 0) {
        pos--;
        lseek(fd, pos, SEEK_SET);
        char c;
        read(fd, &c, 1);

        if (c == '\n' || pos == 0) {
            // Znaleziono poczatek linii (lub poczatek pliku)
            off_t start_line = (pos == 0) ? 0 : pos + 1;
            off_t len = end_line - start_line;
            
            if (len > 0) {
                lseek(fd, start_line, SEEK_SET);
                char *buf = malloc(len);
                read(fd, buf, len);
                write(1, buf, len);
                write(1, "\n", 1);
                free(buf);
            }
            end_line = pos;
        }
    }
    close(fd);
    return 0;
}