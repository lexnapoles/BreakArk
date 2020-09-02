#include "Paddle.h"

Paddle::Paddle(int posX, int posY)
        :Quadrilateral(posX, posY)
{
	paddleState.x = posX;
	paddleState.v = 0;
	collider.w = PADDLE_WIDTH;
	collider.h = PADDLE_HEIGHT;
}

void Paddle::HandleInput(SDL_Event& e)
{
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:   paddleState.v -= PADDLE_VEL; true; break;
		case SDLK_RIGHT: paddleState.v += PADDLE_VEL; true; break;
		}
	}

	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:   paddleState.v += PADDLE_VEL; true; break;
		case SDLK_RIGHT: paddleState.v -= PADDLE_VEL; true;  break;
		}
	}
}

void Paddle::HandleInput(PaddleInput input)
{
    if (input.leftDown)
    {
        paddleState.v -= PADDLE_VEL;
    }
    else if (input.rightDown)
    {
        paddleState.v += PADDLE_VEL;
    }    
    else if (input.leftUp)
    {
        paddleState.v += PADDLE_VEL;
    }
    else if (input.rigthUp)
    {
        paddleState.v -= PADDLE_VEL;
    }
}

void Paddle::Move(double t, double dt)
{
	Integrate(paddleState, t, dt);
	posX = paddleState.x;
	ShiftCollider();
}

void Paddle::SetPosX(int x)
{
	paddleState.x = x;
	posX = paddleState.x;
	ShiftCollider();
}

void Paddle::SetPosY(int y)
{
	posY = y;
	ShiftCollider();
}

