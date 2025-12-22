#include <stdio.h>
#include <unistd.h>

int main() {
    // Wypisanie napisu początkowego
    printf("Poczatek\n");

    // Zastąpienie bieżącego procesu programem 'ls' (wyświetlenie katalogu)
    execlp("ls", "ls", "-l", NULL);

    // Ten kod jest nieosiągalny, jeśli execlp się powiedzie!
    printf("Koniec\n");

    return 0;
}