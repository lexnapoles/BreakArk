#ifndef PADDLE_H
#define	PADDLE_H

#include "Quadrilateral.h"

struct PaddleInput
{
    bool leftUp;
    bool leftDown;
    bool rigthUp;
    bool rightDown;
};

class Paddle : public Quadrilateral 
{
public:
	static const int PADDLE_WIDTH = 150;
	static const int PADDLE_HEIGHT = 20;
	static const int PADDLE_VEL = 500;
    
    Paddle(int posX, int posY);
    
	void HandleInput(SDL_Event& e);
    void HandleInput(PaddleInput input);
    
    void Move(double t, double dt);
    
    //Getters
    double GetVelX() { return paddleState.v; }
	double GetPosX() { return paddleState.x; }
   
	//Setters
	void SetPosX(int x);
	void SetPosY(int y);
    
private:
	State paddleState;
};


#endif /* PADDLE_H */
