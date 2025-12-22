/* zadanie19.c */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;
    
    struct stat sb;
    if (stat(argv[1], &sb) == -1) {
        perror("stat");
        return 1;
    }

    printf("Plik: %s\n", argv[1]);
    printf("Rozmiar: %ld bajtow\n", sb.st_size);
    printf("Uprawnienia: %o\n", sb.st_mode & 0777);
    printf("Inody: %ld\n", sb.st_ino);
    
    // Wlasciciel
    struct passwd *pw = getpwuid(sb.st_uid);
    struct group  *gr = getgrgid(sb.st_gid);
    printf("Wlasciciel: %s (%d)\n", pw ? pw->pw_name : "unknown", sb.st_uid);
    printf("Grupa: %s (%d)\n", gr ? gr->gr_name : "unknown", sb.st_gid);

    printf("Ostatnia modyfikacja: %s", ctime(&sb.st_mtime));

    return 0;
}