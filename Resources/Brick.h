
#ifndef BRICK_H
#define	BRICK_H

#include "Quadrilateral.h"

class Brick : public Quadrilateral
{
public:
	//Type representing the "hardness" of the brick (the impacts it can endure before being destroyed) 
	//None means the brick has been destroyed (it won't be rendered)
	enum HARDNESS { NONE, SOFT, MEDIUM, HARD };
    static const int BRICK_WIDTH = 160;
    static const int BRICK_HEIGHT = 60;

	Brick(int posX, int posY, HARDNESS hardness, int id);

	int GetHardness() { return (int)hardness; }
        int GetID() { return id; }
        
    bool IsDestroyed() { return !hardness; }
	
	//do nothing
	void Move() { return; }
	
	void DecreaseHardness();
	void DestroyBrick() { hardness = NONE; }
	
private:
	HARDNESS hardness;
        int id; //number that helps identifying the block easily without the coordinates
};

#endif	/* BRICK_H */