/* zadanie14.c */
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void reverse_and_print(char *str, int len) {
    for (int i = len - 1; i >= 0; i--) {
        write(1, &str[i], 1);
    }
    write(1, "\n", 1);
}

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;
    int fd = open(argv[1], O_RDONLY);
    
    char line[1024];
    int idx = 0;
    char c;

    while (read(fd, &c, 1) > 0) {
        if (c == '\n') {
            reverse_and_print(line, idx);
            idx = 0;
        } else {
            if(idx < 1024) line[idx++] = c;
        }
    }
    if (idx > 0) reverse_and_print(line, idx); // ostatnia linia bez entera
    close(fd);
    return 0;
}