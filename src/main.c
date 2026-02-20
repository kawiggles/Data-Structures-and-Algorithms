#include "manage.h"
#include <stdio.h>

int main() {
    char input[256];

    while (1) {
        printf("buildstruct> ");
        fgets(input, sizeof(input), stdin);
        parseInput(input);
    }

    return 0;
}