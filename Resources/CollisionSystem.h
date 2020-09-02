#ifndef COLLISIONSYSTEM_H
#define	COLLISIONSYSTEM_H

#include "Ball.h"
#include "Brick.h"
#include "Paddle.h"
#include "MathHelperFunctions.h"
#include <vector>


class CollisionSystem
{
public:
	CollisionSystem();
	~CollisionSystem();

	void UpdateCollisions(Ball& ball, Paddle& paddle, std::vector<Brick*>& bricks, const int screenWidth,  const int screenHeight, 
		                  const double t, const double dt, std::vector<int>& bricksDestroyed);

private:
	//Circle/Circle collision detector
	bool CheckCollision(const Circle &a, const Circle &b);

	//Circle/Box collision detector
	bool CheckCollision(const Circle &a, const SDL_Rect &b);
        
	bool CheckCollision(const Circle& a, std::vector<Brick*>& bricks, Brick*& brick);
        
    //Paddle/walls collision detector
    bool CheckCollision(const SDL_Rect& a, const int screenWidth);

	//Circle/walls collision detector
	void BallWallsCollision(Ball& ball, const int screenWidth, const int screenHeight);
       
	void PaddleBallCollision(Ball& ball, Paddle& paddle);

	void InvertBallVelocity(Ball& ball, const SDL_Rect& b);

	//Calculates Closest point between circle and rectangle
	void ClosestPtCircleRect(const Circle& a, const SDL_Rect& b, int& pX, int& pY);
        
};

#endif	/* COLLISIONSYSTEM_H */