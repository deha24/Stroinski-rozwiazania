/* zadanie10.c */
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 3) return 1; // Minimum 1 zrodlo i 1 cel

    // Ostatni argument to cel
    int dest_fd = open(argv[argc-1], O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (dest_fd == -1) return 1;

    char buf[1024];
    ssize_t n;

    // Iteruj przez wszystkie pliki oprocz ostatniego (celu) i pierwszego (nazwa programu)
    for (int i = 1; i < argc - 1; i++) {
        int src_fd = open(argv[i], O_RDONLY);
        if (src_fd != -1) {
            while ((n = read(src_fd, buf, sizeof(buf))) > 0) {
                write(dest_fd, buf, n);
            }
            close(src_fd);
        } else {
            perror(argv[i]);
        }
    }
    close(dest_fd);
    return 0;
}