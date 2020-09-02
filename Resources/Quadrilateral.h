#ifndef QUADRILATERAL_H
#define	QUADRILATERAL_H

#include "Object.h"

class Quadrilateral  : public Object 
{
public:
Quadrilateral (int posX, int posY);

    SDL_Rect GetCollider() { return collider; } 
        
	int GetPosY() { return posY; }

	void Render(SDL_Renderer *renderer);
	
protected:
	int posX, posY;
        
	//Collider
	SDL_Rect collider;
	
	void ShiftCollider();

};

#endif /* QUADRILATERAL_H */