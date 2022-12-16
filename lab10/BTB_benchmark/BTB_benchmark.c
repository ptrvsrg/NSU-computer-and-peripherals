#include <stdio.h>
#include <stdlib.h>

#include "branches.h"
#include "papi.h"

int main()
{
    int retval = PAPI_library_init(PAPI_VER_CURRENT);
    if (retval != PAPI_VER_CURRENT)
    {
        fprintf(stderr, "%s\n", PAPI_strerror(retval));
        return EXIT_FAILURE;
    }

    int events[] = {
        PAPI_BR_MSP,    // Conditional branch instructions mispredicted
        PAPI_BR_INS     // Total branch instructions executed
    };
    long long values[2];

    retval = PAPI_start_counters(events, sizeof(events) / sizeof(*events));
    if (retval != PAPI_OK)
    {
        fprintf(stderr, "%s\n", PAPI_strerror(retval));
        return EXIT_FAILURE;
    }

    for (int i = 0; i < 100000; ++i)
        RunBranches();

    retval = PAPI_stop_counters(values, sizeof(values) / sizeof(*values));
    if (retval != PAPI_OK)
    {
        fprintf(stderr, "%s\n", PAPI_strerror(retval));
        return EXIT_FAILURE;
    }

    printf("Branch misses percentage: %lf\n", (double)values[0] * 100 / (double)values[1]);

    return EXIT_SUCCESS;
}