#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double MonteCarloAlgorithm(int count)
{
    double insideCount = 0.0;
    srand(time(NULL));

    for (int i = 0; i < count; ++i)
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

int main()
{
    unsigned int count = 100000000;

    double pi = MonteCarloAlgorithm(count);
    printf("PI: %lf\n", pi);

    return EXIT_SUCCESS;
}