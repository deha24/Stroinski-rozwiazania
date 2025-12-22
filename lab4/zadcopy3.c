#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void alarm_handler(int sig) {
    printf("\n[ALARM] Czas minął!\n");
    exit(0);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Podaj liczbę sekund jako parametr!\n");
        return 1;
    }

    signal(SIGALRM, alarm_handler);
    alarm(atoi(argv[1])); // Ustawienie timera

    printf("Alarm ustawiony. Wykonuję inne zadania...\n");

    while(1) {
        printf(".");
        fflush(stdout);
        sleep(1);
    }
    return 0;
}