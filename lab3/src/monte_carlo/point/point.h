#ifndef POINT_H
#define POINT_H

#include <stdbool.h>
#include "random.h"

typedef struct Point
{
    double x, y;
} Point;

Point InitPoint(void);
bool InsideCircle(Point point);

#endif // POINT_H