#include <iostream>

#include "monte_carlo.h"

using namespace std;

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        cerr << "No point count\n";
        return EXIT_FAILURE;
    }
    
    long long count = atoll(argv[1]);

    if (count < 0)
    {
        cerr << "Wrong point count\n";
        return EXIT_FAILURE;
    }

    cout << MonteCarloAlgorithm(count) << "\n";

    return EXIT_SUCCESS;
}