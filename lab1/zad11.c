/* zadanie11.c */
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int fd = 0;
    if (argc > 1) fd = open(argv[1], O_RDONLY);
    
    char c;
    int in_word = 0;
    long count = 0;

    while (read(fd, &c, 1) > 0) {
        if (isalnum(c) || c == '_') {
            if (!in_word) {
                in_word = 1;
                count++;
            }
        } else {
            in_word = 0;
        }
    }
    
    printf("Liczba slow: %d\n", count);
    if (fd != 0) close(fd);
    return 0;
}