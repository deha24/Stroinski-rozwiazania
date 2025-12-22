#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    printf("--- Pierwszy fork ---\n");
    
    // Pierwsze rozdwojenie procesu
    fork(); 
    
    // Wypisanie identyfikatorów po pierwszym forku (wykonają to 2 procesy)
    printf("PID: %d, PPID: %d\n", getpid(), getppid());

    printf("--- Drugi fork ---\n");

    // Każdy z istniejących procesów tworzy potomka
    fork();

    // Wypisanie identyfikatorów po drugim forku (wykonają to 4 procesy)
    printf("PID: %d, PPID: %d\n", getpid(), getppid());

    return 0;
}