//Ball Class

#ifndef BALL_H
#define	BALL_H


#include "Object.h"

struct Circle
{
	double x, y;
	double r;
};

class Ball : public Object
{
public:
	static const int BALL_WIDTH = 20;
	static const int BALL_HEIGHT = 20;

	Ball(int posX, int posY, int velX, int velY);

	void Move(const double t, const double dt);

	void Render(SDL_Renderer* renderer);

	//Getters
	const double GetPosX() { return ballStateX.x; }
	const double GetPosY() { return ballStateY.x; }
    const double GetVelX() { return ballStateX.v; }
    const double GetVelY () { return ballStateY.v; }
        
	//Setters
	void SetVelX(double velX) { ballStateX.v = velX; }
	void SetVelY(double velY) { ballStateY.v = velY; }
        
    void SetPosX(double posX) { ballStateX.x = posX; }
	void SetPosY(double posY) { ballStateY.x = posY; }
         
    void InvertVelX() { ballStateX.v = -ballStateX.v; }
    void InvertVelY() { ballStateY.v = -ballStateY.v; };
        
    Circle& GetCollider() { return collider; }

private:

	State ballStateX;
	State ballStateY;

	Circle collider;

	void ShiftCollider();
};


#endif	/* BALL_H */
