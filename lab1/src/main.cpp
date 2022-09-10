#include <iostream>
#include "monte_carlo.h"

#ifdef SYS_TYME
    #include <ctime>
#endif // SYS_TYME

#ifdef PROC_TIME
    #include <sys/times.h>
    #include <unistd.h>
#endif // PROC_TIME

#ifdef CPU_TIME_STAMP_COUNTER
    #define CPU_HZ 2100000000ULL
#endif // CPU_TIME_STAMP_COUNTER

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

#ifdef SYS_TYME
    struct timespec sysStart, sysEnd;
    clock_gettime(CLOCK_MONOTONIC_RAW, &sysStart);
#endif // SYS_TYME

#ifdef PROC_TIME
    struct tms procStart, procEnd;
    long clocks_per_sec = sysconf(_SC_CLK_TCK);
    long clocks;
    times(&procStart);
#endif // PROC_TIME

#ifdef CPU_TIME_STAMP_COUNTER
    union {
        unsigned long long t64;
        struct { 
            unsigned long th, tl; 
        } t32;
    } tactStart, tactEnd;
    asm("rdtsc\n":"=a"(tactStart.t32.th),"=d"(tactStart.t32.tl));
#endif // CPU_TIME_STAMP_COUNTER

    double pi = MonteCarloAlgorithm(count);

#ifdef SYS_TYME
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    double sysTime = sysEnd.tv_sec - sysStart.tv_sec + 1e-9 * (sysEnd.tv_nsec - sysStart.tv_nsec);
    cout << "System time: " << sysTime << " sec.\n";
#endif // SYS_TYME

#ifdef PROC_TIME
    times(&procEnd);
    double procTime = (double)(procEnd.tms_utime - procStart.tms_utime) / clocks_per_sec;
    cout << "Process time: " << procTime << "sec.\n";
#endif // PROC_TIME

#ifdef CPU_TIME_STAMP_COUNTER
    asm("rdtsc\n":"=a"(tactEnd.t32.th),"=d"(tactEnd.t32.tl));
    double tactTime = (double)(tactEnd.t64 - tactStart.t64) / CPU_HZ;
    cout << "CPU time stamp counter: " << tactTime << " sec.\n";
#endif // CPU_TIME_STAMP_COUNTER

    cout << "PI: " << pi << "\n";

    return EXIT_SUCCESS;
}