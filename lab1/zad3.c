/* zadanie3.c */
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) return 1;

    int in = open(argv[1], O_RDONLY);
    int out = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    
    if (in == -1 || out == -1) { perror("open"); return 1; }

    char buf[BUF_SIZE];
    ssize_t n;
    while ((n = read(in, buf, BUF_SIZE)) > 0) {
        write(out, buf, n);
    }

    close(in);
    close(out);
    return 0;
}