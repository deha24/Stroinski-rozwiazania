/* Zestaw 3, Zadanie 3: Klient-Serwer (ls do prywatnej kolejki) */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

#define PUBLIC_FIFO "/tmp/serwer_fifo"

// Kod SERWERA
void server_code() {
    mkfifo(PUBLIC_FIFO, 0666);
    char client_fifo_name[256];

    printf("[Serwer] Czekam na zgłoszenia...\n");
    while(1) {
        int public_fd = open(PUBLIC_FIFO, O_RDONLY);
        int n = read(public_fd, client_fifo_name, sizeof(client_fifo_name));
        close(public_fd);

        if (n > 0) {
            printf("[Serwer] Otrzymałem zgłoszenie od klienta: %s\n", client_fifo_name);
            
            if (fork() == 0) {
                // Proces obsługujący żądanie
                int client_fd = open(client_fifo_name, O_WRONLY);
                dup2(client_fd, STDOUT_FILENO); // Przekierowanie stdout do kolejki klienta
                close(client_fd);
                execlp("ls", "ls", NULL); // Wykonanie ls
                exit(1);
            }
            wait(NULL); // Czekamy aż podproces wyśle dane
        } else {
             // Brak danych (np. klient zamknął połączenie), wyjście z pętli dla celów demo
             break;
        }
    }
    unlink(PUBLIC_FIFO);
}

// Kod KLIENTA
void client_code(int id) {
    char my_fifo[50];
    sprintf(my_fifo, "/tmp/client_%d_fifo", getpid());
    mkfifo(my_fifo, 0666);

    // 1. Wyślij nazwę swojej kolejki do serwera
    printf("[Klient %d] Wysyłam zapytanie...\n", id);
    int public_fd = open(PUBLIC_FIFO, O_WRONLY);
    write(public_fd, my_fifo, strlen(my_fifo) + 1);
    close(public_fd);

    // 2. Czekaj na odpowiedź w swojej kolejce
    int my_fd = open(my_fifo, O_RDONLY);
    char buf[1024];
    printf("[Klient %d] --- Wynik polecenia ls ---\n", id);
    while(read(my_fd, buf, sizeof(buf)) > 0) {
        printf("%s", buf);
    }
    printf("\n[Klient %d] --- Koniec transmisji ---\n", id);
    
    close(my_fd);
    unlink(my_fifo);
    exit(0);
}

int main() {
    // Uruchamiamy serwer w procesie potomnym (dla symulacji w jednym pliku)
    if (fork() == 0) {
        server_code();
        exit(0);
    }
    
    sleep(1); // Czas na start serwera

    // Uruchamiamy klienta
    if (fork() == 0) {
        client_code(1);
    }

    // Rodzic (symulator) czeka
    wait(NULL); wait(NULL);
    return 0;
}