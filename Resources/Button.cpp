#include "Brick.h"


Brick::Brick(int posX, int posY, HARDNESS hardness, int id)
: Quadrilateral(posX, posY)
{
    this->hardness = hardness;
    collider.w = BRICK_WIDTH;
    collider.h = BRICK_HEIGHT;
    
    this->id = id;
        
}


void Brick::DecreaseHardness()
{
    if (hardness)
    {
        int aux = hardness;
        hardness = (HARDNESS)--aux;
    }
}
