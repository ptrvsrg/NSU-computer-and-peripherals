#include <stdio.h>
#include <stdlib.h>

#include "branches.h"

int main()
{
    for (int i = 0; i < 1000000; ++i)
        RunBranches();

    return EXIT_SUCCESS;
}