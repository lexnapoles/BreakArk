#include "Ball.h"


Ball::Ball(int posX, int posY, int velX, int velY)
{
	//Initiate states (2D position and velocity)
	ballStateX.x = posX;
	ballStateX.v = velX;
	ballStateY.x = posY;
	ballStateY.v = velY;	

	//Set collider
	collider.r = BALL_WIDTH / 2;
	ShiftCollider();
}

void Ball::Move(const double t, const double dt)
{
	//Obtain new positions and velocities using RK4 integration method
	Integrate(ballStateX, t, dt);
	Integrate(ballStateY, t, dt);

	ShiftCollider();
}

void Ball::Render(SDL_Renderer *renderer)
{
	if (objectTexture == NULL)
	{
		std::cerr << "Ball's texture is not initiated" << std::endl;
		return;
	}

	//Render coordinates must be adjusted. The ball's position is in its center, but to render we need to pass the coordinates of the top left position.
	objectTexture->Render((int)(ballStateX.x - collider.r), (int)(ballStateY.x - collider.r), renderer);
}

void Ball::ShiftCollider()
{
	//Align collider to center of dot
	collider.x = ballStateX.x;
	collider.y = ballStateY.x;
}

