#include "monte_carlo.h"

double MonteCarloAlgorithm(long long count)
{
    InitRand();

    double insideCount = 0.0;
    for (long long i = 0; i < count; ++i)
    {
        Point a = InitPoint();
        if (InsideCircle(a))
        {
            insideCount += 4.0;
        }
    }

    return insideCount / count;
}
