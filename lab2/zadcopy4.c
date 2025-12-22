#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    printf("Poczatek\n");

    // Tworzymy proces potomny dla komendy ls
    if (fork() == 0) {
        // Kod dziecka: uruchamia ls i kończy swoje działanie
        execlp("ls", "ls", "-l", NULL);
        exit(1); // Wyjście awaryjne, jeśli exec zawiedzie
    } else {
        // Kod rodzica: czeka na zakończenie dziecka
        wait(NULL);
        
        // Po powrocie dziecka wypisujemy koniec
        printf("Koniec\n");
    }

    return 0;
}