/* Zadanie 1: Przesłanie komunikatu Hello */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <sys/wait.h>

// Struktura wiadomości
struct msgbuf {
    long mtype;       // Typ komunikatu (musi być > 0)
    char mtext[100];  // Treść
};

int main() {
    // Tworzymy kolejkę prywatną (tylko dla procesów spokrewnionych)
    int msgid = msgget(IPC_PRIVATE, 0666 | IPC_CREAT);
    if (msgid == -1) { perror("msgget"); return 1; }

    if (fork() == 0) {
        // --- PROCES POTOMNY (NADAWCA) ---
        struct msgbuf msg;
        msg.mtype = 1; 
        strcpy(msg.mtext, "Hello");

        // msgsnd(id, struktura, rozmiar_danych, flagi)
        // Rozmiar to sizeof(mtext), nie całej struktury!
        msgsnd(msgid, &msg, sizeof(msg.mtext), 0);
        printf("[Dziecko] Wysłano: %s\n", msg.mtext);
        exit(0);
    } else {
        // --- PROCES RODZICA (ODBIORCA) ---
        struct msgbuf msg;
        
        // msgrcv(id, struktura, rozmiar, typ, flagi)
        msgrcv(msgid, &msg, sizeof(msg.mtext), 1, 0);
        printf("[Rodzic] Odebrano: %s\n", msg.mtext);

        wait(NULL);
        // Usunięcie kolejki
        msgctl(msgid, IPC_RMID, NULL);
    }
    return 0;
}