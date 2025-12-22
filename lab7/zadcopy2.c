/* Zestaw 3, Zadanie 2: Złożony potok (ps | tr | cut | sort | uniq | sort) */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Funkcja pomocnicza do obsługi błędów i duplikacji deskryptorów
void run_stage(int input_fd, int output_fd, char *cmd, char *arg1, char *arg2, char *arg3) {
    pid_t pid = fork();
    if (pid == 0) {
        if (input_fd != 0) {
            dup2(input_fd, 0); // Wejście z poprzedniej rury
            close(input_fd);
        }
        if (output_fd != 1) {
            dup2(output_fd, 1); // Wyjście do następnej rury
            close(output_fd);
        }
        // Uruchomienie polecenia
        execlp(cmd, cmd, arg1, arg2, arg3, NULL);
        perror("Błąd exec");
        exit(1);
    }
}

int main() {
    int p1[2], p2[2], p3[2], p4[2], p5[2];

    // Tworzymy wszystkie rury
    pipe(p1); pipe(p2); pipe(p3); pipe(p4); pipe(p5);

    // 1. ps -ef
    run_stage(0, p1[1], "ps", "-ef", NULL, NULL);
    close(p1[1]); // Rodzic zamyka końcówki, których nie używa

    // 2. tr -s ' ' :
    run_stage(p1[0], p2[1], "tr", "-s", " ", ":");
    close(p1[0]); close(p2[1]);

    // 3. cut -d: -f1
    run_stage(p2[0], p3[1], "cut", "-d:", "-f1", NULL);
    close(p2[0]); close(p3[1]);

    // 4. sort
    run_stage(p3[0], p4[1], "sort", NULL, NULL, NULL);
    close(p3[0]); close(p4[1]);

    // 5. uniq -c
    run_stage(p4[0], p5[1], "uniq", "-c", NULL, NULL);
    close(p4[0]); close(p5[1]);

    // 6. sort -n (wypisuje na ekran, więc output_fd = 1)
    run_stage(p5[0], 1, "sort", "-n", NULL, NULL);
    close(p5[0]);

    // Czekamy na wszystkie 6 procesów
    for(int i=0; i<6; i++) wait(NULL);

    return 0;
}