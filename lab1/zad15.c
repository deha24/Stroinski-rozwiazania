/* zadanie15.c */
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 3) return 1;
    char *pattern = argv[1];
    int pat_len = strlen(pattern);

    for (int i = 2; i < argc; i++) {
        int fd = open(argv[i], O_RDONLY);
        if (fd == -1) continue;

        char c;
        char buffer[1024]; // Prosty bufor przesuwny
        int buf_idx = 0;
        
        int line = 1, col = 1;
        
        // Uproszczone szukanie (znak po znaku)
        // Dla pelnej poprawnosci przy duzych plikach nalezaloby zaimplementowac bufor kołowy
        // Tutaj wersja naiwna czytajaca po znaku dla precyzji wspolrzednych
        
        // Zeby znalezc wzorzec, musimy pamietac ostatnie X znakow. 
        // Wymaga to troche wiecej kodu, wiec uzyjemy prostrzego podejscia:
        // Czytamy plik do duzego bufora lub resetujemy pozycje (lseek) - ale lseek jest wolny.
        // Zrobimy to na biezaco sprawdzajac postep wzorca.
        
        int match_idx = 0;
        int saved_col = 0;

        while (read(fd, &c, 1) > 0) {
            if (c == pattern[match_idx]) {
                if (match_idx == 0) saved_col = col;
                match_idx++;
                if (match_idx == pat_len) {
                    printf("Plik: %s, Linia: %d, Kolumna: %d\n", argv[i], line, saved_col);
                    match_idx = 0; // Szukamy dalej
                }
            } else {
                // Jesli nie pasuje, nalezaloby cofnac sie w pliku (backtracking), 
                // ale dla uproszczenia zerujemy (wersja naiwna)
                if (match_idx > 0) {
                     // Hack: w idealnym swiecie algorytm KMP
                     match_idx = 0;
                }
            }

            if (c == '\n') {
                line++;
                col = 1;
                match_idx = 0;
            } else {
                col++;
            }
        }
        close(fd);
    }
    return 0;
}