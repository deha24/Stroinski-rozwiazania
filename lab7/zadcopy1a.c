/* Zadanie 1a: Pisarz (uruchom pierwszy) */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 1024

int main() {
    
    // Tworzymy pamięć (lub pobieramy jeśli istnieje)
    int shmid = shmget(1234, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) { perror("shmget"); return 1; }

    // Dołączamy pamięć
    char *data = (char*)shmat(shmid, NULL, 0);
    
    printf("[Pisarz] Uruchomiony. Piszę do pamięci...\n");

    while(1) {
        // Zapis "haaaa"
        strcpy(data, "haaaa");
        // sleep(1); // Opcjonalne spowolnienie dla obserwacji

        // Zapis "hoooooo"
        strcpy(data, "hoooooo");
        // sleep(1); 
    }

    // Odłączenie (teoretycznie nieosiągalne w pętli while(1))
    shmdt(data);
    return 0;
}