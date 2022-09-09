#include <iostream>
#include "monte_carlo.h"

#if defined USE_CLOCK_GETTIME
    #include <ctime> // for clock_gettime
#elif defined USE_TIMES
    #include <sys/times.h> // for times
    #include <unistd.h> //  for sysconf
#elif defined USE_RDTSC
    #define CPU_HZ 2100000000ULL
#endif

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

#if defined USE_CLOCK_GETTIME
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
#elif defined USE_TIMES
    struct tms start, end;
    long clocks_per_sec = sysconf(_SC_CLK_TCK);
    long clocks;
    times(&start);
#elif defined USE_RDTSC
    union {
        unsigned long long t64;
        struct { 
            long th, tl; 
        } t32;
    } start, end;
    asm("rdtsc\n":"=a"(start.t32.th),"=d"(start.t32.tl));
#endif

    double pi = MonteCarloAlgorithm(count);

#ifdef USE_CLOCK_GETTIME
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    cout << "System time: " << end.tv_sec - start.tv_sec + 0.000000001 * (end.tv_nsec - start.tv_nsec) << " sec.\n";
#elif defined USE_TIMES
    times(&end);
    cout << "Process time: " << (double)(end.tms_utime - start.tms_utime) / clocks_per_sec << "sec.\n";
#elif defined USE_RDTSC
    asm("rdtsc\n":"=a"(end.t32.th),"=d"(end.t32.tl));
    cout << "CPU time stamp counter: " << (double)(end.t64 - start.t64) / CPU_HZ << " sec.\n";
#endif

    cout << "PI: " << pi << "\n";

    return EXIT_SUCCESS;
}