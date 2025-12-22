/* Zadanie 4: Implementacja funkcji sleep */
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

// Pusta funkcja obsługi - aby sygnał nie zabił procesu, tylko go obudził z pause()
void wakeup(int sig) {}

void my_sleep(unsigned int seconds) {
    // 1. Zapisz starą obsługę (opcjonalne, dla porządku)
    void (*old_handler)(int) = signal(SIGALRM, wakeup);
    
    // 2. Ustaw budzik
    alarm(seconds);
    
    // 3. Czekaj na jakikolwiek sygnał
    pause();
    
    // 4. Przywróć obsługę (opcjonalne)
    signal(SIGALRM, old_handler);
}

int main() {
    printf("Zaczynam my_sleep(3)...\n");
    my_sleep(3);
    printf("Obudziłem się po 3 sekundach!\n");
    return 0;
}