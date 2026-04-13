#include "manage.h"
#include <stdio.h>
#include <HsFFI.h>

int main(int argc, char *argv[]) {
    printf("buildstruct is running! Type \"help\" for help and \"quit\" to quit: \n");

    hs_init(&argc, &argv);

    char input[256];

    while (1) {
        printf("buildstruct> ");
        fgets(input, sizeof(input), stdin);
        if (parseInput(input)) break;
    }

    return 0;
}
