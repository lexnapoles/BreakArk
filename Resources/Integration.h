//Integration formulas of the RK4 integration method

#ifndef INTEGRATION_H
#define	INTEGRATION_H

#include <cmath>

struct State
{
	double x;
	double v;
};

struct Derivative
{
	double dx;
	double dv;
};

double Acceleration(const State &state, double t);

Derivative Evaluate(const State &Initial, double t);

Derivative Evaluate(const State &Initial, double t, double dt, const Derivative &d);

void Integrate(State &state, double t, double dt);

#endif /* INTEGRATION_H */