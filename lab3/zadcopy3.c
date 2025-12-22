/* Zadanie 3: Alarm i wykonywanie innych zadań */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void komunikat(int sig) {
    printf("\n\n[ALARM] Minął zadany czas! Sygnał %d odebrany.\n", sig);
    exit(0); // Zakończ program po alarmie
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Użycie: %s <liczba_sekund>\n", argv[0]);
        return 1;
    }
    
    int sekundy = atoi(argv[1]);

    // Rejestracja obsługi sygnału alarmu
    signal(SIGALRM, komunikat);
    
    // Ustawienie timera systemowego
    alarm(sekundy); 

    printf("Alarm ustawiony na %d s. Wykonuję 'inne zadania'...\n", sekundy);

    // Symulacja pracy głównego programu
    while(1) {
        printf("."); 
        fflush(stdout); // Wymuś wypisanie kropki natychmiast
        sleep(1);
    }
    return 0;
}