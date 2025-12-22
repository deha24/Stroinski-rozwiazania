/* zadanie7.c */
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void copy_last_10_bytes(int src_fd, int dest_fd) {
    off_t size = lseek(src_fd, 0, SEEK_END);
    off_t start = (size >= 10) ? size - 10 : 0;
    
    lseek(src_fd, start, SEEK_SET);
    
    char buf[1024];
    ssize_t n = read(src_fd, buf, sizeof(buf));
    write(dest_fd, buf, n);
}

int main(int argc, char *argv[]) {
    // Proste wywolanie dla przykladu
    if(argc != 3) return 1;
    int in = open(argv[1], O_RDONLY);
    int out = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0644);
    copy_last_10_bytes(in, out);
    close(in); close(out);
    return 0;
}