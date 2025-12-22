/* Zadanie 4: Serwer sumujący */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>

// Definicje typów komunikatów
#define M_DANE  1
#define M_END   2
#define M_WYNIK 3

struct num_msg {
    long mtype;
    int value;  // Przesyłamy liczbę zamiast tekstu
};

int main() {
    int msgid = msgget(IPC_PRIVATE, 0666 | IPC_CREAT);

    if (fork() == 0) {
        // --- SERWER ---
        struct num_msg msg;
        int suma = 0;
        int running = 1;

        while(running) {
            // Odbieramy dowolny komunikat (typ 0), ale >0 (np. -3 oznacza priorytety)
            // Tutaj prościej: odbieramy typ -3 (czyli 1, 2 lub 3 - dowolny najmniejszy)
            // Ale bezpieczniej jawnie sprawdzać typ po odbiorze.
            msgrcv(msgid, &msg, sizeof(int), 0, 0);

            if (msg.mtype == M_DANE) {
                suma += msg.value;
            } else if (msg.mtype == M_END) {
                // Koniec danych, odsyłamy wynik
                msg.mtype = M_WYNIK;
                msg.value = suma;
                msgsnd(msgid, &msg, sizeof(int), 0);
                running = 0;
            }
        }
        exit(0);
    } else {
        // --- KLIENT ---
        struct num_msg msg;
        int liczby[] = {5, 10, 20, 7};
        
        printf("[Klient] Wysyłam liczby do sumowania...\n");
        for(int i=0; i<4; i++) {
            msg.mtype = M_DANE;
            msg.value = liczby[i];
            msgsnd(msgid, &msg, sizeof(int), 0);
            printf("Wysłano: %d\n", liczby[i]);
        }
        
        // Wysłanie znacznika końca
        msg.mtype = M_END;
        msgsnd(msgid, &msg, sizeof(int), 0);

        // Odbiór wyniku
        msgrcv(msgid, &msg, sizeof(int), M_WYNIK, 0);
        printf("[Klient] Otrzymana suma: %d\n", msg.value);

        wait(NULL);
        msgctl(msgid, IPC_RMID, NULL);
    }
    return 0;
}