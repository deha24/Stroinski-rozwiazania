/* Zestaw 3, Zadanie 1: FIFO Hello */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

#define FIFO_NAME "test_fifo"

int main() {
    // 1. Tworzenie kolejki FIFO (prawa rw-rw-rw-)
    if (mkfifo(FIFO_NAME, 0666) == -1) {
        perror("Błąd mkfifo (może plik już istnieje)");
    }

    if (fork() == 0) {
        // --- PROCES POTOMNY (ZAPIS) ---
        printf("[Potomek] Otwieram FIFO do zapisu...\n");
        int fd = open(FIFO_NAME, O_WRONLY);
        
        char *msg = "HALLO!";
        write(fd, msg, strlen(msg) + 1); // +1 dla znaku końca linii/stringa
        
        close(fd);
        exit(0);
    } else {
        // --- PROCES RODZICA (ODCZYT) ---
        printf("[Rodzic] Otwieram FIFO do odczytu...\n");
        int fd = open(FIFO_NAME, O_RDONLY);
        
        char buf[50];
        read(fd, buf, sizeof(buf));
        printf("[Rodzic] Odebrano: %s\n", buf);
        
        close(fd);
        wait(NULL); // Czekamy na dziecko
        unlink(FIFO_NAME); // Sprzątanie pliku
    }

    return 0;
}