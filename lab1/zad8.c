/* zadanie8.c */
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;
    int fd = open(argv[1], O_RDONLY);
    
    char buf[512];
    ssize_t n;
    int is_text = 1;

    while ((n = read(fd, buf, sizeof(buf))) > 0) {
        for (int i = 0; i < n; i++) {
            if (!isascii(buf[i])) {
                is_text = 0;
                break;
            }
        }
        if (!is_text) break;
    }
    
    printf("Plik %s %s tekstowy.\n", argv[1], is_text ? "JEST" : "NIE JEST");
    close(fd);
    return 0;
}