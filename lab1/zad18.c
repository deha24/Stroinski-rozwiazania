/* zadanie18.c */
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    struct dirent **namelist;
    int n;
    const char *dir = (argc > 1) ? argv[1] : ".";

    // scandir alokuje pamięć i zwraca liczbę wpisów
    n = scandir(dir, &namelist, NULL, alphasort);
    if (n < 0) {
        perror("scandir");
        return 1;
    } else {
        while (n--) {
            printf("%s\n", namelist[n]->d_name);
            free(namelist[n]);
        }
        free(namelist);
    }
    return 0;
}