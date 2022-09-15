#include "point.h"

Point InitPoint()
{
    Point point = {
        .x = GenerateRand(),
        .y = GenerateRand()
    };

    return point;
}

bool InsideCircle(Point point)
{
    return (point.x * point.x) + (point.y * point.y) <= 1.0;
}
