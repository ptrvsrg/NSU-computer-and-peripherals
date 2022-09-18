#include "monte_carlo.h"

double MonteCarloAlgorithm(long long count)
{
    InitRand();

    double insideCount = 0.0;
    for (long long i = 0; i < count; ++i)
    {
        TPoint point = InitPoint();
        if (InsideCircle(point))
        {
            insideCount += 4.0;
        }
    }

    return insideCount / count;
}