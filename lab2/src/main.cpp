#include <iostream>
#include <ctime>

#include "monte_carlo.h"

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        std::cerr << "No point count\n";
        return EXIT_FAILURE;
    }
    
    long long count = atoll(argv[1]);

    if (count < 0)
    {
        std::cerr << "Wrong point count\n";
        return EXIT_FAILURE;
    }

    struct timespec sysStart, sysEnd;
    clock_gettime(CLOCK_MONOTONIC_RAW, &sysStart);

    double pi = MonteCarloAlgorithm(count);

    clock_gettime(CLOCK_MONOTONIC_RAW, &sysEnd);
    double sysTime = sysEnd.tv_sec - sysStart.tv_sec + 1e-9 * (sysEnd.tv_nsec - sysStart.tv_nsec);
    std::cout << "System time: " << sysTime << " sec.\n";

    std::cout << "PI: " << pi << "\n";

    return EXIT_SUCCESS;
}