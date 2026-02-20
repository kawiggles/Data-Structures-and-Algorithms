#include "manage.h"
#include <stdio.h>

int main() {
    char input[256];

    while (1) {
        printf("buildstruct> ");
        fgets(input, sizeof(input), stdin);
        if (parseInput(input)) break;
    }

    return 0;
}