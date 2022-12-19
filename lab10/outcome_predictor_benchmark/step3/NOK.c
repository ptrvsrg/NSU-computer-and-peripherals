#include <stdio.h>
#include <stdlib.h>

int main (int argc, char ** argv)
{
    if (argc < 4)
    {
        fprintf(stderr, "Few args error\n");
        return EXIT_FAILURE;
    }

    int n1 = atoi(argv[1]);
    int n2 = atoi(argv[2]);
    int max = atoi(argv[3]);
    int nok = 1;

    do
    {
        if (nok % n1 == 0 && nok % n2 == 0)
            return nok > max;

        ++nok;
    } while (1);
}