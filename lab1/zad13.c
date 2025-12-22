/* zadanie13.c */
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;
    char *pattern = argv[1];
    
    char line_buf[1024];
    int idx = 0;
    char c;

    // Czytamy ze STDIN (0)
    while (read(0, &c, 1) > 0) {
        if (c != '\n' && idx < 1023) {
            line_buf[idx++] = c;
        } else {
            line_buf[idx] = '\0'; // Koniec stringa
            if (strstr(line_buf, pattern)) {
                write(1, line_buf, idx);
                write(1, "\n", 1);
            }
            idx = 0;
        }
    }
    return 0;
}