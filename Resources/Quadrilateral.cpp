#include "Quadrilateral.h"

Quadrilateral ::Quadrilateral (int posX, int posY)
{
    this->posX = posX;
    this->posY = posY;
	
    ShiftCollider();
}

void Quadrilateral ::ShiftCollider()
{
	//Align collider 
	collider.x = posX;
	collider.y = posY;
}

void Quadrilateral ::Render(SDL_Renderer* renderer)
{
 	objectTexture->Render(posX, posY, renderer);
}