#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a = 1;
    for (int i = 0; i < 100000000; ++i)
    {
        if (i < 0) a = 1;           // dummy branch #1
        if (i < 0) a = 1;           // dummy branch #2
        if (i < 0) a = 1;           // dummy branch #3
        if (i < 0) a = 1;           // dummy branch #4
        if (i < 0) a = 1;           // dummy branch #5
        if (i < 0) a = 1;           // dummy branch #6
        if (i < 0) a = 1;           // dummy branch #7
        if (i < 0) a = 1;           // dummy branch #8
        if (i < 0) a = 1;           // dummy branch #9
        if (i < 0) a = 1;           // dummy branch #10
        if (i < 0) a = 1;           // dummy branch #11
        if (i < 0) a = 1;           // dummy branch #12
        if (i < 0) a = 1;           // dummy branch #13
        if (i < 0) a = 1;           // dummy branch #14
        if (i < 0) a = 1;           // dummy branch #15
        if (i < 0) a = 1;           // dummy branch #16
        if (i < 0) a = 1;           // dummy branch #17
        if (i < 0) a = 1;           // dummy branch #18
        if (i < 0) a = 1;           // dummy branch #19
        if (i < 0) a = 1;           // dummy branch #20
        if (i < 0) a = 1;           // dummy branch #21
        if (i < 0) a = 1;           // dummy branch #22
        if (i < 0) a = 1;           // dummy branch #23
        if (i < 0) a = 1;           // dummy branch #24
        if (i < 0) a = 1;           // dummy branch #25
        if (i < 0) a = 1;           // dummy branch #26
        if (i < 0) a = 1;           // dummy branch #27
        if (i < 0) a = 1;           // dummy branch #28
        if (i < 0) a = 1;           // dummy branch #29
        if (i < 0) a = 1;           // dummy branch #30
        if (i < 0) a = 1;           // dummy branch #31
        if (i < 0) a = 1;           // dummy branch #32
        if (i < 0) a = 1;           // dummy branch #33
        if (i < 0) a = 1;           // dummy branch #34
        if ((i % 18) == 0) a = 0;   // spy branch
    }

    // it is necessary that during optimization
    // it is not deleted as unused variable
    if (a == 12345)
        printf("Wow");

    return EXIT_SUCCESS;
}