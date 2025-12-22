/* zadanie12.c */
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;
    int fd = open(argv[1], O_RDONLY);
    
    long counts[26] = {0};
    long total = 0;
    char c;

    while (read(fd, &c, 1) > 0) {
        if (isalpha(c)) {
            c = tolower(c);
            counts[c - 'a']++;
            total++;
        }
    }
    
    if (total > 0) {
        for (int i = 0; i < 26; i++) {
            printf("%c: %.2f%%\n", 'a'+i, (counts[i] * 100.0) / total);
        }
    }
    close(fd);
    return 0;
}