#include <stdio.h>
#include <inttypes.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char lnxpath[4096] = {0};
    char winpath[4096] = {0};
    char plfpath[4096] = {0};
    if (argc == 2) {
        strcpy(lnxpath, argv[1]);
        sprintf(winpath, "%s.exe", lnxpath);
        sprintf(plfpath, "%s.pelf", lnxpath);
    } else if (argc == 3) {
        strcpy(lnxpath, argv[1]);
        strcpy(winpath, argv[2]);
        sprintf(plfpath, "%s.pelf", lnxpath);
    } else if (argc == 4) {
        strcpy(lnxpath, argv[1]);
        strcpy(winpath, argv[2]);
        strcpy(plfpath, argv[3]);
    } else {
        printf("Incorrect usage: %s elf_file [pe_file] [pelf_file]\n", argv[0]);
        return 1;
    }
    printf("%s %s %s\n", lnxpath, winpath, plfpath);
}
