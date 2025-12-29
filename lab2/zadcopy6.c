#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    // Pętla wykonuje się 3 razy
    for (int i = 0; i < 3; i++) {
        if (fork() == 0) {
            // Kod dziecka:
            printf("Potomek %d (PID: %d) kończy działanie.\n", i+1, getpid());
            // Dziecko kończy się natychmiast (staje się zombie, bo rodzic nie zrobił wait)
            exit(0); 
        }
    }

    // Kod rodzica:
    // Rodzic śpi przez 15 sekund i NIE wywołuje wait().
    // W tym czasie dzieci są "martwe", ale wciąż wiszą w tablicy procesów jako <defunct> (zombie).
    printf("Rodzic śpi, sprawdź procesy poleceniem 'ps' (poniżej):\n");
   
    if(fork() == 0){
        execlp("ps", "ps", NULL);
        exit(0);
    }
    sleep(15); 
    
    printf("Rodzic kończy działanie (zombie zostaną usunięte przez init/system).\n");
    return 0;
}