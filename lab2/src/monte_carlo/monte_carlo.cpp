#include "monte_carlo.h"

#pragma GCC push_options
#ifdef O0
    #pragma GCC optimize("O0")
#endif // O0
#ifdef O1
    #pragma GCC optimize("O1")
#endif // O1
#ifdef O2
    #pragma GCC optimize("O2")
#endif // O2
#ifdef O3
    #pragma GCC optimize("O3")
#endif // O3
#ifdef Os
    #pragma GCC optimize("Os")
#endif // Os
#ifdef Ofast
    #pragma GCC optimize("Ofast")
#endif // Ofast
#ifdef Og
    #pragma GCC optimize("Og")
#endif // Og

double MonteCarloAlgorithm(long long count)
{
    InitRand();

    double insideCount = 0.0;
    for (long long i = 0; i < count; ++i)
    {
        Point a;
        if (a.InsideCircle())
        {
            insideCount += 4.0;
        }
    }

    return insideCount / count;
}

#pragma GCC pop_options