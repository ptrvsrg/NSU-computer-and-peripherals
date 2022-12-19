#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Few args error\n");
        return EXIT_FAILURE;
    }

    int LSpy = atoi(argv[1]);
    int a = 1;

    for (int i = 0; i < 10000000; ++i)
        if ((i % LSpy) == 0) a = 0;    // spy branch

    // it is necessary that during optimization
    // it is not deleted as unused variable
    if (a == 12345)
        printf("Wow");

    return EXIT_SUCCESS;
}