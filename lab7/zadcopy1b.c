/* Zadanie 1b: Czytelnik (uruchom w drugim terminalu) */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 1024

int main() {
    // Ten sam klucz co u Pisarza
    key_t key = ftok(".", 'S');
    
    // Pobieramy ID istniejącej pamięci
    int shmid = shmget(key, SHM_SIZE, 0666);
    if (shmid == -1) { 
        printf("Nie znaleziono pamięci! Uruchom najpierw program 1a.\n");
        return 1; 
    }

    char *data = (char*)shmat(shmid, NULL, 0);
    printf("[Czytelnik] Podłączono. Weryfikacja danych...\n");

    while(1) {
        // Sprawdzamy zawartość
        // Uwaga: Bez semaforów może się zdarzyć, że odczytamy "śmieci" 
        // w momencie gdy pisarz jest w trakcie kopiowania napisu.
        if (strcmp(data, "haaaa") != 0 && strcmp(data, "hoooooo") != 0) {
            printf("BŁĄD! Odczytano niepoprawny napis: '%s'\n", data);
        }
        // Brak błędu = cisza (lub można wypisywać OK)
    }

    shmdt(data);
    // Usuwamy pamięć dopiero w czytelniku (np. po Ctrl+C i obsłudze sygnału, 
    // tu dla uproszczenia po wyjściu z pętli)
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}