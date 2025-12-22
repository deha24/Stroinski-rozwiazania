#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handler(int sig) {
    if (sig == SIGINT) printf("\nOdebrano SIGINT (Ctrl-C)\n");
    else if (sig == SIGTSTP) printf("\nOdebrano SIGTSTP (Ctrl-Z)\n");
    else if (sig == SIGQUIT) printf("\nOdebrano SIGQUIT (Ctrl-\\)\n");
}

int main() {
    // Rejestracja sygnałów
    signal(SIGINT, handler);
    signal(SIGTSTP, handler);
    signal(SIGQUIT, handler);

    printf("Naciskaj kombinacje klawiszy (Ctrl-C, Ctrl-Z, Ctrl-\\)...\n");
    
    while(1) {
        pause(); // Czeka na sygnał
    }
    return 0;
}