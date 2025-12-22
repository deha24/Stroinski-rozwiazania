/* Zestaw 3, Zadanie 5: Pierścień procesów FIFO */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Użycie: %s <liczba_procesow>\n", argv[0]);
        return 1;
    }
    int N = atoi(argv[1]);
    char fifo_names[N][64];

    // 1. Generujemy nazwy i tworzymy kolejki FIFO
    for (int i = 0; i < N; i++) {
        sprintf(fifo_names[i], "/tmp/ring_fifo_%d", i);
        mkfifo(fifo_names[i], 0666);
    }

    int i;
    for (i = 0; i < N; i++) {
        if (fork() == 0) {
            // --- KOD PROCESU i ---
            // Ustalamy indeksy: czytam od siebie (i), piszę do następnego (i+1)%N
            // Uwaga: Żeby uniknąć zakleszczenia (deadlock) przy open,
            // proces startowy (0) najpierw otwiera zapis, a reszta najpierw odczyt.
            
            int fd_read, fd_write;
            char buffer[1024];

            if (i == 0) {
                // LIDER (Proces 0)
                printf("[P0] Startuję. Otwieram zapis do %d...\n", (i+1)%N);
                fd_write = open(fifo_names[(i+1)%N], O_WRONLY);
                
                // Inicjacja wiadomości
                sprintf(buffer, "TOKEN:%d", getpid());
                write(fd_write, buffer, strlen(buffer) + 1);
                printf("[P0] Wysłano: %s\n", buffer);
                
                // Teraz otwieram odczyt, żeby odebrać po pełnym okrążeniu
                fd_read = open(fifo_names[i], O_RDONLY);
                read(fd_read, buffer, sizeof(buffer));
                printf("[P0] Odebrano po okrążeniu: %s\n", buffer);
                
            } else {
                // POZOSTAŁE PROCESY
                // Najpierw odczyt (czekam na poprzednika)
                fd_read = open(fifo_names[i], O_RDONLY);
                read(fd_read, buffer, sizeof(buffer));
                
                printf("[P%d] Odebrano: %s\n", i, buffer);
                
                // Dopisanie swojego PID
                char tmp[64];
                sprintf(tmp, "-%d", getpid());
                strcat(buffer, tmp);
                
                // Przekazanie dalej
                fd_write = open(fifo_names[(i+1)%N], O_WRONLY);
                write(fd_write, buffer, strlen(buffer) + 1);
            }

            // Sprzątanie w procesie
            close(fd_read);
            close(fd_write);
            exit(0);
        }
    }

    // Rodzic czeka na wszystkie dzieci
    for (int k = 0; k < N; k++) wait(NULL);

    // Usuwanie plików FIFO
    for (int k = 0; k < N; k++) unlink(fifo_names[k]);
    
    printf("Koniec symulacji pierścienia.\n");
    return 0;
}