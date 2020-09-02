#include "CollisionSystem.h"


CollisionSystem::CollisionSystem()
{
}


CollisionSystem::~CollisionSystem()
{
}

void CollisionSystem::UpdateCollisions(Ball& ball, Paddle& paddle, std::vector<Brick*>& bricks, const int screenWidth, const int screenHeight,
	                                   const double t, const double dt, std::vector<int>& bricksDestroyed)
{
/*
Check if there are collisions and update the state of the objects involved in it.
  
  Collisions checked: 
            Ball - Paddle 
            Ball - Walls  
            Paddle - Walls       
            Ball - Bricks 
			
   Changes in the state:
           Ball :  velocity inversion
	       Bricks : hardness reduction
	 
It does this recursively until there's no more collisions
*/

    //Ball - Paddle
    if (CheckCollision(ball.GetCollider(), paddle.GetCollider()))
    {
        PaddleBallCollision(ball, paddle);
    }
    
    //Ball - Walls
	BallWallsCollision(ball, screenWidth, screenHeight);
    	
    //Paddle - Walls    
    if (CheckCollision(paddle.GetCollider(), screenWidth) )
    {
		//Move back
		if (paddle.GetPosX() < 0 )
		{
			paddle.SetPosX(0);
		}
		else if (paddle.GetPosX() + Paddle::PADDLE_WIDTH > screenWidth)
		{
			paddle.SetPosX(screenWidth - Paddle::PADDLE_WIDTH);
			
		}
    }
            
    //Ball - Bricks
    double time = t;
	Brick* brick = NULL;

	if (CheckCollision(ball.GetCollider(), bricks, brick))
	{
		brick->DecreaseHardness();

		if (brick->GetHardness() == 0)
		{
			bricksDestroyed.push_back(brick->GetID());
		}
        
        InvertBallVelocity(ball, brick->GetCollider());
        
        ball.Move(t, dt);
        
        time += dt;
        
		UpdateCollisions(ball, paddle, bricks, screenWidth, screenHeight, time, dt, bricksDestroyed);
    }
}

bool CollisionSystem::CheckCollision(const Circle& a, const SDL_Rect& b)
{
	//Closest point on collision box
	int pX, pY;
	ClosestPtCircleRect(a, b, pX, pY);

	//If the Closest point is inside the circle
	return DistanceSquared(a.x, a.y, pX, pY) < a.r * a.r;
}

bool CollisionSystem::CheckCollision(const Circle& a, std::vector<Brick*>& bricks, Brick*& brick)
{
	std::vector<Brick*>::iterator it;
	for (it = bricks.begin(); it != bricks.end(); ++it)
	{
		if (!(*it)->IsDestroyed() && CheckCollision(a, (*it)->GetCollider()))
		{
			brick = *it;
			return true;
		}
	}

	return false;


}


bool CollisionSystem::CheckCollision(const SDL_Rect& a, const int screenWidth)
{
    return a.x < 0 || a.x + a.w > screenWidth;
}

void CollisionSystem::PaddleBallCollision(Ball& ball, Paddle& paddle)
{
  	const double paddlePosX = paddle.GetPosX();
	const double paddlePosY = paddle.GetPosY();
	const double ballCenterX = ball.GetPosX();
	const double ballCenterY = ball.GetPosY();

	int pX, pY;
	ClosestPtCircleRect(ball.GetCollider(), paddle.GetCollider(), pX, pY);
	
	//First region   
	if ((ballCenterX < paddlePosX || ballCenterX > paddlePosX + Paddle::PADDLE_WIDTH) && (ballCenterY < paddlePosY))
	{
		ball.InvertVelY();
	}

	//Second region
	else if ((ballCenterX < paddlePosX || ballCenterX > paddlePosX + Paddle::PADDLE_WIDTH) && (ballCenterY >= paddlePosY && ballCenterY <= paddlePosY + Paddle::PADDLE_HEIGHT))
	{
		if (ballCenterX < paddlePosX)
		{
			ball.SetPosX(paddlePosX - ball.GetCollider().r);
		}
		else if (ballCenterX > paddlePosX + Paddle::PADDLE_WIDTH)
		{
			ball.SetPosX(paddlePosX + Paddle::PADDLE_WIDTH + ball.GetCollider().r);
		}

		ball.InvertVelX();
	}

	//Third region
    else if ((ballCenterX >= paddlePosX || ballCenterX <= paddlePosX + Paddle::PADDLE_WIDTH) && (ballCenterY < paddlePosY))
	{
		ball.SetPosY(paddlePosY - ball.GetCollider().r);
		ball.InvertVelY();
	}
  
}

void CollisionSystem::BallWallsCollision(Ball& ball, const int screenWidth, const int screenHeight)
{
	int x, y, d;

	Circle a = ball.GetCollider();

	x = a.x - a.r;
	y = a.y - a.r;
	d = 2 * a.r; //diameter

	//Left wall
	if (x < 0)
	{
		ball.InvertVelX();
		ball.SetPosX(ball.GetCollider().r);
	}
	
	//Right wall
	else if (x + d > screenWidth)
	{
		ball.InvertVelX();
		ball.SetPosX(screenWidth - ball.GetCollider().r);
	}

	//Upper wall
	if (y < 0)
	{
		ball.InvertVelY();
		ball.SetPosY(ball.GetCollider().r);
	}

	/*
	else if (y + d > screenHeight)
	{
		ball.InvertVelY();
		ball.SetPosY(screenHeight - ball.GetCollider().r);
	}
	*/
}


void  CollisionSystem::ClosestPtCircleRect(const Circle& a, const SDL_Rect& b, int& pX, int& pY)
{
	// If the center is outside the rectangle, clamp it to the rectangle
	// Else the center is the closest point

	// Closest point to the collision box
	double x, y;

	x = a.x;
	y = a.y;
    
	// Find closest x offset	
	if (a.x < b.x)
	{
		x = b.x;
	}
	if (a.x > b.x + b.w)
	{
		x = b.x + b.w;
	}
	
	//Find closest y offset
	if (a.y < b.y)
	{
		y = b.y;
	}
   if (a.y > b.y + b.h)
	{
		y = b.y + b.h;
	}

	pX = x;
	pY = y;
}

void CollisionSystem::InvertBallVelocity(Ball& ball, const SDL_Rect& b)
{
	Circle a = ball.GetCollider();

	//If the ball's center is at the left or right of the brick invert X velocity
	if (a.x <= b.x || a.x >= b.x + b.w)
	{
		ball.InvertVelX();
	}

	//If the ball's center is at the top or bottom of the brick invert Y velocity
	if (a.y <= b.y || a.y >= b.y + b.h)
	{
		ball.InvertVelY();
	}
}