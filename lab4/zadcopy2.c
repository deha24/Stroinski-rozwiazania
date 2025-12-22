#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main() {
    signal(SIGINT, SIG_IGN); // SIG_IGN = Ignore

    printf("Sygnał SIGINT jest ignorowany. Spróbuj Ctrl-C.\n");
    printf("Program zakończy się samoczynnie za 5 sekund.\n");
    
    sleep(5);
    return 0;
}