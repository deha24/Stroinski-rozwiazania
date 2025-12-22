/* Zadanie 5: Chat asynchroniczny */
/* Kompilacja: gcc chat.c -o chat 
   Uruchomienie T1: ./chat 1
   Uruchomienie T2: ./chat 2 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <signal.h>

struct msgbuf {
    long mtype;       // ID Adresata
    char mtext[256];
};

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Użycie: %s <moje_id (1 lub 2)>\n", argv[0]);
        return 1;
    }
    
    int my_id = atoi(argv[1]);
    int dest_id = (my_id == 1) ? 2 : 1; // Jeśli ja jestem 1, ślę do 2 (i vice versa)

    // Generujemy klucz, żeby oba programy połączyły się do tej samej kolejki
    key_t key = ftok(".", 'B'); 
    int msgid = msgget(key, 0666 | IPC_CREAT);

    printf("Jesteś użytkownikiem %d. Piszesz do %d. Wpisz 'exit' by zakończyć.\n", my_id, dest_id);

    pid_t pid = fork();

    if (pid == 0) {
        // --- PROCES DZIECKA (ODBIERANIE) ---
        struct msgbuf msg;
        while(1) {
            // Czekam na wiadomości skierowane DO MNIE (my_id)
            if (msgrcv(msgid, &msg, sizeof(msg.mtext), my_id, 0) != -1) {
                if (strcmp(msg.mtext, "exit") == 0) {
                    printf("\n[Rozmówca się rozłączył]\n");
                    kill(getppid(), SIGTERM); // Zabij rodzica (pisanie)
                    exit(0);
                }
                printf("\n>> Otrzymano: %s\nTy: ", msg.mtext);
                fflush(stdout); // Wymuszenie odświeżenia prompta
            }
        }
    } else {
        // --- PROCES RODZICA (PISANIE) ---
        struct msgbuf msg;
        msg.mtype = dest_id; // Adresujemy do rozmówcy
        size_t len;

        while(1) {
            printf("Ty: ");
            if (fgets(msg.mtext, sizeof(msg.mtext), stdin) == NULL) break;
            
            // Usunięcie entera z końca
            len = strlen(msg.mtext);
            if (len > 0 && msg.mtext[len-1] == '\n') msg.mtext[len-1] = '\0';

            // Wysłanie
            msgsnd(msgid, &msg, sizeof(msg.mtext), 0);

            if (strcmp(msg.mtext, "exit") == 0) {
                kill(pid, SIGKILL); // Zabijamy proces nasłuchujący
                break;
            }
        }
        // Pierwszy wychodzący usuwa kolejkę (opcjonalne, w chacie "trwałym" nie usuwamy)
        msgctl(msgid, IPC_RMID, NULL);
    }
    return 0;
}