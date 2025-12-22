/* Zadanie 7: Pętle ls i ps */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    if (fork() == 0) {
        // --- Proces A: wykonuje ciągle ls ---
        while(1) {
            printf("\n[Proces A] Uruchamiam ls:\n");
            if (fork() == 0) {
                execlp("ls", "ls", NULL);
                exit(1);
            }
            wait(NULL); // Czeka na zakończenie ls
            sleep(2);   // Pauza dla czytelności
        }
    } else {
        // --- Proces B: wykonuje ciągle ps ---
        while(1) {
            printf("\n[Proces B] Uruchamiam ps:\n");
            if (fork() == 0) {
                execlp("ps", "ps", NULL);
                exit(1);
            }
            wait(NULL); // Czeka na zakończenie ps
            sleep(2);
        }
    }
    return 0;
}