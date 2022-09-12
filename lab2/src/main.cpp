#include <iostream>
#include <sys/times.h>
#include <unistd.h>

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

    struct tms procStart, procEnd;
    long clocks_per_sec = sysconf(_SC_CLK_TCK);
    long clocks;
    times(&procStart);

    double pi = MonteCarloAlgorithm(count);

    times(&procEnd);
    double procTime = (double)(procEnd.tms_utime - procStart.tms_utime) / clocks_per_sec;
    cout << "Process time: " << procTime << "sec.\n";

    cout << "PI: " << pi << "\n";

    return EXIT_SUCCESS;
}