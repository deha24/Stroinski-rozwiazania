#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Podaj nazwę pliku jako argument!\n");
        return 1;
    }

    if (fork() == 0) {
        // --- Proces potomny ---
        
        // 1. Otwieramy (lub tworzymy) plik do zapisu
        // O_WRONLY: tylko zapis, O_CREAT: utwórz jeśli nie ma, O_TRUNC: wyczyść jeśli jest
        // 0644: uprawnienia do pliku
        int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1) {
            perror("Błąd otwarcia pliku");
            exit(1);
        }

        // 2. Podmieniamy STDOUT (ekran) na nasz plik
        // Od teraz wszystko co proces wypisze printf-em lub systemowo, trafi do pliku
        dup2(fd, STDOUT_FILENO);
        
        // 3. Zamykamy oryginalny deskryptor pliku (nie jest już potrzebny, mamy kopię pod nr 1)
        close(fd);

        // 4. Uruchamiamy ps ax
        execlp("ps", "ps", "ax", NULL);
        
        // Jeśli execlp zadziała, poniższy kod się nie wykona
        perror("Błąd execlp");
        exit(1);
    } else {
        // --- Proces rodzica ---
        wait(NULL); // Czekamy aż dziecko skończy pisać do pliku
        printf("Zapisano wynik 'ps ax' do pliku: %s\n", argv[1]);
    }

    return 0;
}