#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double MonteCarloAlgorithm(long long count)
{
    srand(time(NULL));

    double insideCount = 0.0;
    for (long long i = 0; i < count; ++i)
    {
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;

        if ((x * x) + (y * y) <= 1.0)
        {
            insideCount += 4.0;
        }
    }

    return insideCount / count;
}

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