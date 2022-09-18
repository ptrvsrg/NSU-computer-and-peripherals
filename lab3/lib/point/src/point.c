#include "point.h"

TPoint InitPoint(void)
{
    TPoint point = {
        .x = GenerateRand(),
        .y = GenerateRand()
    };

    return point;
}

bool InsideCircle(TPoint point)
{
    return (point.x * point.x) + (point.y * point.y) <= 1.0;
}
