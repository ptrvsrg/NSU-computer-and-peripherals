#ifndef POINT_H
#define POINT_H

#include <stdbool.h>
#include "random.h"

typedef struct
{
    double x, y;
} TPoint;

TPoint InitPoint(void);
bool InsideCircle(TPoint point);

#endif // POINT_H