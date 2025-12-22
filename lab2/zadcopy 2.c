#include <stdio.h>
#include <unistd.h>

int main() {
    // Wypisanie napisu przed podziałem
    printf("Poczatek\n");

    // Rozdwojenie procesu
    fork();

    // Ten fragment wykona zarówno rodzic, jak i dziecko
    printf("Koniec\n");

    return 0;
}