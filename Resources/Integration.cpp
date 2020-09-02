#include "Integration.h"


double Acceleration(const State &state, double t)
{
	// We would write here the function that calculates the acceleration of the object, 
	// since we don't need acceleration in the game we return 0

	/* e.g Acceleration calculated as a spring and damper force 
	
	const double k = 10;
	const double b = 1;
	return -k*state.x - b*state.v;
	
	*/
	
	return 0.0;

}

Derivative Evaluate(const State &Initial, double t)
{
	Derivative output;
	output.dx = Initial.v;
	output.dv = Acceleration(Initial, t);
	return output;
}

Derivative Evaluate(const State &Initial, double t, double dt, const Derivative &d)
{
	State state;
	state.x = Initial.x + d.dx*dt;
	state.v = Initial.v + d.dv*dt;

	Derivative output;
	output.dx = state.v;
	output.dv = Acceleration(state, t + dt);

	return output;
}

void Integrate(State &state, double t, double dt)
{
	Derivative a = Evaluate(state, t);
	Derivative b = Evaluate(state, t, dt*0.5f, a);
	Derivative c = Evaluate(state, t, dt*0.5f, b);
	Derivative d = Evaluate(state, t, dt, c);

	const double dxdt = 1.0f / 6.0f * (a.dx + 2.0f*(b.dx + c.dx) + d.dx);
	const double dvdt = 1.0f / 6.0f * (a.dv + 2.0f*(b.dv + c.dv) + d.dv);

	state.x = state.x + dxdt*dt;
	state.v = state.v + dvdt*dt;
}
