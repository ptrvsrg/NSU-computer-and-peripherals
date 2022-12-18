#include <stdio.h>
#include <stdlib.h>

#include "papi.h"

int main(int argc, char ** argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Few args error\n");
        return EXIT_FAILURE;
    }

    int LSpy = atoi(argv[1]);

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

    int a = 1;
    for (int i = 0; i < 10000000; ++i)
        if ((i % LSpy) == 0) a = 0;    // spy branch

    retval = PAPI_stop_counters(values, sizeof(values) / sizeof(*values));
    if (retval != PAPI_OK)
    {
        fprintf(stderr, "%s\n", PAPI_strerror(retval));
        return EXIT_FAILURE;
    }

    // it is necessary that during optimization
    // it is not deleted as unused variable
    if (a == 12345)
        printf("Wow");

    printf("%lf", (double)values[0] * 100 / (double)values[1]);

    return EXIT_SUCCESS;
}