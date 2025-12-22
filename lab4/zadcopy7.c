#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    if (fork() == 0) {
        while(1) { // Pętla ls
            if(fork() == 0) { execlp("ls", "ls", NULL); exit(1); }
            wait(NULL);
            sleep(1);
        }
    } else {
        while(1) { // Pętla ps
            if(fork() == 0) { execlp("ps", "ps", NULL); exit(1); }
            wait(NULL);
            sleep(1);
        }
    }
    return 0;
}