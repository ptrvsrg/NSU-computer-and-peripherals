#include <stdio.h>
#include <stdlib.h>

#include "monte_carlo.h"

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        fprintf(stderr, "No point count\n");
        return EXIT_FAILURE;
    }

    long long count = atoll(argv[1]);

    if (count < 0)
    {
        fprintf(stderr, "Wrong point count\n");
        return EXIT_FAILURE;
    }

    double pi = MonteCarloAlgorithm(count);
    printf("PI: %lf\n", pi);

    return EXIT_SUCCESS;
}