#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void wakeup(int sig) {
    // Pusta funkcja - tylko po to, by przerwać pause()
}

void my_sleep(int seconds) {
    signal(SIGALRM, wakeup);
    alarm(seconds);
    pause(); // Czeka na jakikolwiek sygnał (tutaj SIGALRM)
}

int main() {
    printf("Usypiam na 3 sekundy...\n");
    my_sleep(3);
    printf("Obudziłem się.\n");
    return 0;
}