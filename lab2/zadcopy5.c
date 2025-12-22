#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    printf("--------poczatek listy-----------\n");

    // Tworzymy proces potomny, aby nie nadpisać głównego programu
    if (fork() == 0) {
        // Uruchomienie komendy ps (lista procesów)
        execlp("ps", "ps", NULL); 
        exit(1);
    } else {
        // Rodzic czeka, aż ps wypisze dane
        wait(NULL);
        
        printf("\n--------koniec listy-------------\n");
    }

    return 0;
}