

#include "cannon.h"
#include <stdio.h>

int main()
{
    initialize_variables();
    printf("\n\n");
    print_initial_conditions();

    int status = 0;
    while (status == 0) {
        // step simulation (update global variables)
        status = step_simulation();
        print_projectile();
    }

    if (status == 1) printf("direct hit\n");
    if (status == 2) printf("missed target\n");
    if (status == 3) printf("timed out\n");
}

