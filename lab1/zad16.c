/* zadanie16.c */
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc < 3) return 1;
    int max_len = atoi(argv[1]);
    
    // Wersja uproszczona: czytamy słowo, sprawdzamy czy wejdzie w linię
    // Separator akapitu (pusta linia) resetuje licznik
    
    for(int i=2; i<argc; i++) {
        int fd = open(argv[i], O_RDONLY);
        if(fd == -1) continue;
        
        char c;
        char word[256];
        int w_idx = 0;
        int current_line_len = 0;
        int newline_streak = 0; // Do wykrywania pustych linii

        while(read(fd, &c, 1) > 0) {
            if(isspace(c)) { //zamiana isspace
                if(w_idx > 0) { // Mamy całe słowo w buforze
                    word[w_idx] = '\0';
                    
                    if(current_line_len + w_idx + (current_line_len > 0 ? 1 : 0) > max_len) {
                        write(1, "\n", 1);
                        current_line_len = 0;
                    }
                    
                    if(current_line_len > 0) {
                        write(1, " ", 1);
                        current_line_len++;
                    }
                    
                    write(1, word, w_idx);
                    current_line_len += w_idx;
                    w_idx = 0;
                    newline_streak = 0;
                }
                
                if (c == '\n') {
                    newline_streak++;
                    if (newline_streak == 2) { // Pusta linia (enter po enterze)
                        write(1, "\n\n", 2);
                        current_line_len = 0;
                        newline_streak = 0;
                    }
                }
            } else {
                if(w_idx < 255) word[w_idx++] = c;
                newline_streak = 0;
            }
        }
        write(1, "\n", 1);
        close(fd);
    }
    return 0;
}