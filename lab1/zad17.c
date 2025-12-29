/* zadanie17.c */
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
    if (argc != 3) return 1;
    int fd1 = open(argv[1], O_RDONLY);
    int fd2 = open(argv[2], O_RDONLY);
    bool changed = false;
    
    char c1, c2;
    int r1, r2;
    int line = 1, pos = 0;
    off_t total1 = 0, total2 = 0;

    // Pobierz rozmiary do sprawdzenia koncowki
    total1 = lseek(fd1, 0, SEEK_END); lseek(fd1, 0, SEEK_SET);
    total2 = lseek(fd2, 0, SEEK_END); lseek(fd2, 0, SEEK_SET);

    while (1) {
        r1 = read(fd1, &c1, 1);
        r2 = read(fd2, &c2, 1);
        pos++;

        if (r1 == 0 && r2 == 0) {
            if (changed==true){
                break;
            }else{
                printf("Pliki są identyczne");
                break;
            }
        }
        
        if (r1 > 0 && r2 > 0) {
            if (c1 != c2) {
                printf("Pliki roznia sie od znaku nr %d w linii %d\n", pos, line);
                changed = true;
            }
            if (c1 == '\n') { line++; pos = 0; }
        } else {
            // Jeden sie skonczyl
            if(changed == false){
                if (r1 > 0) printf("Plik %s zawiera %d znakow wiecej\n", argv[1], total1 - total2);
                else printf("Plik %s zawiera %d znakow wiecej\n", argv[2], total2 - total1);
                break;
            }
        }
    }
    close(fd1); close(fd2);
    return 0;
}