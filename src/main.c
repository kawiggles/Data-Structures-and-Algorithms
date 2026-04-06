#include "manage.h"
#include <stdio.h>

int main() {
    printf("buildstruct is running! Type \"help\" for help and \"quit\" to quit: \n");

    char input[256];

    while (1) {
        printf("buildstruct> ");
        fgets(input, sizeof(input), stdin);
        if (parseInput(input)) break;
    }

    return 0;
}
