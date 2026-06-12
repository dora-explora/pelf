#include <stdio.h>

int main() {
    #ifdef __linux__
        printf("Hello, Linux!\n");
    #else
        printf("Hello, Windows!\n");
    #endif
}
