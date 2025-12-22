/* Zadanie 2: Pszczoły i Misie */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>

// Liczba zwierząt
#define LICZBA_PSZCZOL 5
#define LICZBA_MISIOW 2

// Struktura w pamięci wspólnej
struct Ul {
    int miod; // Ilość miodu w kg
};

void pszczola(int id, struct Ul *ul) {
    int total_zaniesiono = 0;
    srand(getpid()); // Unikalne ziarno losowości

    while(1) {
        int ile = 1 + rand() % 5; // Pszczoła niesie 1-5 kg
        sleep(1 + rand() % 3);    // Czas lotu

        // Sekcja krytyczna (modyfikacja pamięci)
        ul->miod += ile;
        total_zaniesiono += ile;

        printf("Pszczoła_%d: zaniosłam %dkg, w ulu jest %dkg (Suma moja: %dkg)\n", 
               id, ile, ul->miod, total_zaniesiono);
    }
}

void mis(int id, struct Ul *ul) {
    int total_zjedzono = 0;
    srand(getpid());

    while(1) {
        int apetyt = 5 + rand() % 10; // Miś chce zjeść 5-14 kg
        sleep(3 + rand() % 5);        // Miś śpi dłużej

        // Sprawdzenie warunku: nie może zjeść więcej niż jest
        if (ul->miod >= apetyt) {
            ul->miod -= apetyt;
            total_zjedzono += apetyt;
            printf("Miś_%d: zjadłem %dkg, zostało %dkg (Suma moja: %dkg)\n", 
                   id, apetyt, ul->miod, total_zjedzono);
        } else {
            printf("Miś_%d: Chciałem %dkg, ale w ulu tylko %dkg. Czekam...\n", 
                   id, apetyt, ul->miod);
        }
    }
}

int main() {
    // 1. Tworzenie pamięci
    int shmid = shmget(IPC_PRIVATE, sizeof(struct Ul), 0666 | IPC_CREAT);
    struct Ul *wspolny_ul = (struct Ul*)shmat(shmid, NULL, 0);
    
    // Inicjalizacja
    wspolny_ul->miod = 0;
    printf("[SYMULACJA] Ul pusty. Wypuszczam pszczoły i misie...\n");

    // 2. Tworzenie Pszczół
    for (int i = 0; i < LICZBA_PSZCZOL; i++) {
        if (fork() == 0) {
            pszczola(i+1, wspolny_ul);
            exit(0);
        }
    }

    // 3. Tworzenie Misiów
    for (int i = 0; i < LICZBA_MISIOW; i++) {
        if (fork() == 0) {
            mis(i+1, wspolny_ul);
            exit(0);
        }
    }

    // Rodzic główny czeka (symulacja nieskończona, przerwij Ctrl+C)
    // W praktyce warto dodać obsługę sygnałów do sprzątania.
    wait(NULL);

    // Sprzątanie (nieosiągalne przy wait(NULL) w pętli nieskończonej dzieci, ale poprawne formalnie)
    shmdt(wspolny_ul);
    shmctl(shmid, IPC_RMID, NULL);
    
    return 0;
}