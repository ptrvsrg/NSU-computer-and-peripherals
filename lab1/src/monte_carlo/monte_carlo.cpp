#include "monte_carlo.h"

double MonteCarloAlgorithm(long long N)
{
    InitRand();

    double M = 0.0;
    for (long long i = 0; i < N; ++i)
    {
        Point a;
        if (a.InsideCircle())
        {
            M += 4.0;
        }
    }

    return M / N;
}
