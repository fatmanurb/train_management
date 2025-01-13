#include <stdio.h>
#include "utils.h"

void clear_screen() {
    printf("\033[H\033[J");
}

void pause_execution() {
    printf("Press Enter to continue...");
    while (getchar() != '\n');
}
