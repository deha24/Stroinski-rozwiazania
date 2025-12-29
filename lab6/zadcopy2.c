/* Zadanie 2: Odbieranie konkretnego typu komunikatu */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <sys/wait.h>

struct msgbuf {
    long mtype;
    char mtext[50];
};

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Użycie: %s <typ_do_odebrania (1-10)>\n", argv[0]);
        return 1;
    }
    long target_type = atol(argv[1]);

    int msgid = msgget(IPC_PRIVATE, 0666 | IPC_CREAT);

    if (fork() == 0) {
        // --- NADAWCA ---
        struct msgbuf msg;
        
        // Wysyłamy serię komunikatów o różnych typach
        for(int i=1; i<=3; i++) {
            msg.mtype = i;
            msgsnd(msgid, &msg, sizeof(msg.mtext), 0);
        }
        printf("[Nadawca] Wysłano wiadomości typów 1, 2, 3.\n");
        exit(0);
    } else {
        // --- ODBIORCA ---
        struct msgbuf msg;
        sleep(1); // Dajemy czas nadawcy

        printf("[Odbiorca] Czekam na typ %ld...\n", target_type);
        
        // Odbieramy TYLKO typ podany w argumencie
        // IPC_NOWAIT sprawi, że nie zablokujemy się, jeśli nie ma takiego typu
        if (msgrcv(msgid, &msg, sizeof(msg.mtext), target_type, IPC_NOWAIT) != -1) {
            printf(">> SUKCES: Odebrano: '%d'\n", target_type);
        } else {
            printf(">> INFO: Brak wiadomości o typie %d w kolejce.\n", target_type);
        }

        // Sprzątanie (wait dla dziecka i usunięcie kolejki)
        wait(NULL);
        msgctl(msgid, IPC_RMID, NULL);
    }
    return 0;
}