#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char lnxpath[4096] = {0};
    char winpath[4096] = {0};
    char plfpath[4096] = {0};
    if (argc == 2) { // if only one argument,
        strcpy(lnxpath, argv[1]); // take lnxpath from argv[1]
        sprintf(winpath, "%s.exe", lnxpath); // and copy it to winpath
        sprintf(plfpath, "%s.pelf", lnxpath); // and plfpath
    } else if (argc == 3) { // if two arguments,
        strcpy(lnxpath, argv[1]); // take lnxpath from argv[1]
        strcpy(winpath, argv[2]); // take winpath from argv[2]
        sprintf(plfpath, "%s.pelf", lnxpath); // and use lnxpath for plfpath
    } else if (argc == 4) { // if three arguments,
        strcpy(lnxpath, argv[1]); // use argv for all 3
        strcpy(winpath, argv[2]);
        strcpy(plfpath, argv[3]);
    } else { // otherwise, print usage message
        printf("Incorrect usage: %s elf_file [pe_file] [pelf_file]\n", argv[0]);
        return 1;
    }

    FILE *lnxfile = fopen(lnxpath, "rb"); // open lnxfile as a binary with read permissions
    FILE *winfile = fopen(winpath, "rb"); // open winfile as a binary with read permissions
    int plffd = open(plfpath, O_RDWR | O_CREAT, 0777);
    FILE *plffile = fdopen(plffd, "wb"); // open/create plffile as an executable binary with write permissions
    if (lnxfile == NULL || winfile == NULL || plffile == NULL) { // if any file couldn't open
        printf("Error opening some file(s):\n"); // return an error message
        if (lnxfile == NULL) { printf("%s could not be opened\n", lnxpath); }
        if (winfile == NULL) { printf("%s could not be opened\n", winpath); }
        if (plffile == NULL) { printf("%s could not be opened\n", plfpath); }
        return 2; // and a failed exit code
    }

    char buffer[1024]; // make buffer for copying/concatenating files
    size_t n; // make var to hold number of bytes actually read
    while ((n = fread(buffer, 1, sizeof(buffer), winfile)) > 0) { // while reading bytes from winfile,
        fwrite(buffer, 1, n, plffile); // write them to plffile
    }
    long s = ftell(winfile); // position of winffile's file pointer is now the size of the file
    while ((n = fread(buffer, 1, sizeof(buffer), lnxfile)) > 0) { // while reading bytes from lnxfile
        fwrite(buffer, 1, n, plffile); // append them to plffile
    }

    fseek(plffile, 0, SEEK_SET); // set plffile's write pointer back to the start
    fprintf(plffile, "MZ=\ntail -c+%ld>p<$0\nchmod +x p\n./p $@&rm p\nexit\n", s + 1); // write the stub

    fclose(lnxfile);
    fclose(winfile);
    fclose(plffile);
    return 0;
}
