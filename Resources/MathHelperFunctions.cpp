#include "MathHelperFunctions.h"

double DistanceSquared(const double x1, const double y1, const double x2, const double y2)
{
    return (x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1);
}

double GetRandomAngle()
{
    srand(time(NULL));
    
    return rand() % 89 + 1; 
}

double DegreesToRadians(double degrees)
{
     return degrees * M_PI/ 180;
}