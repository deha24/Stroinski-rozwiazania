/* Zadanie 3: Serwer Uppercase */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h>

struct msgbuf {
    long mtype;       // 1 = do serwera, 2 = do klienta
    char mtext[256];
};

int main() {
    int msgid = msgget(IPC_PRIVATE, 0666 | IPC_CREAT);

    if (fork() == 0) {
        // --- SERWER ---
        struct msgbuf msg;
        while(1) {
            // Odbierz typ 1 (zapytanie)
            if (msgrcv(msgid, &msg, sizeof(msg.mtext), 1, 0) == -1) break;
            
            // Konwersja na duże litery
            for(int i=0; msg.mtext[i]; i++) {
                msg.mtext[i] = toupper(msg.mtext[i]);
            }
            
            // Odeślij jako typ 2 (odpowiedź)
            msg.mtype = 2;
            msgsnd(msgid, &msg, sizeof(msg.mtext), 0);
            
            // Dla celów demonstracyjnych kończymy po 1 obsłudze
            break; 
        }
        exit(0);
    } else {
        // --- KLIENT ---
        struct msgbuf msg;
        msg.mtype = 1;
        strcpy(msg.mtext, "ala ma kota");
        
        printf("[Klient] Wysyłam: %s\n", msg.mtext);
        msgsnd(msgid, &msg, sizeof(msg.mtext), 0);
        
        // Czekaj na odpowiedź (typ 2)
        msgrcv(msgid, &msg, sizeof(msg.mtext), 2, 0);
        printf("[Klient] Odebrałem: %s\n", msg.mtext);
        
        wait(NULL);
        msgctl(msgid, IPC_RMID, NULL);
    }
    return 0;
}