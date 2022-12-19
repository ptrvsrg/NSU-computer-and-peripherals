#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
    if (argc < 3)
    {
        fprintf(stderr, "Few args error\n");
        return EXIT_FAILURE;
    }

    int L1 = atoi(argv[1]);
    int L2 = atoi(argv[2]);
    int a = 0;
    int b = 0;
    int c = 0;

    for (int i = 0;i < 10000000; ++i)
    {
        if ((i % L1) == 0)  a = 1;
        else                a = 0;
        if ((i % L2) == 0)  b = 1;
        else                b = 0;
        if ((a * b) == 1)   c = 1; // spy branch
    }

    // it is necessary that during optimization
    // it is not deleted as unused variable
    if (a == 12345)
        printf("Wow");
    if (b == 12345)
        printf("Wow");
    if (c == 12345)
        printf("Wow");

    return EXIT_SUCCESS;
}