/* 
 * File:   MathHelperFunctions.h
 * Author: EX350002
 *
 * Created on 9 de junio de 2014, 16:22
 */

#ifndef MATHHELPERFUNCTIONS_H
#define	MATHHELPERFUNCTIONS_H

#define _USE_MATH_DEFINES //Visual Studio does not let you use the constants in cmath without this

#include <cmath>
#include <cstdlib>
#include <ctime>

//Calculates distance squared between two points
double DistanceSquared(const double x1, const double y1, const double x2, const double y2);

//Return random angle between 0 and 90
double GetRandomAngle(); 

double DegreesToRadians(double degrees);


#endif	/* MATHHELPERFUNCTIONS_H */

