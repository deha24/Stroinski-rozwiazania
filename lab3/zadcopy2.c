/* Zadanie 2: Ignorowanie SIGINT */
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main() {
    // Ustawienie ignorowania sygnału SIGINT
    signal(SIGINT, SIG_IGN);

    printf("Naciśnij Ctrl-C - nic się nie stanie.\n");
    printf("Program zakończy się automatycznie za 10 sekund.\n");

    sleep(10); // Czas na testowanie
    
    printf("Koniec czasu.\n");
    return 0;
}