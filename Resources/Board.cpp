/* 
 * File:   Board.cpp
 * Author: EX350002
 * 
 * Created on 29 de mayo de 2014, 14:00
 */

#include "Board.h"

Board::Board(int posX, int posY) {
    
    //The Starting position from where the bricks are going to be drawn 
    x = posX;
    y = posY;
    
    level = 0;
    
    //Save level files
    levels.push_back("..\\BreakArk_Client\\Levels\\level0.txt");
    levels.push_back("..\\BreakArk_Client\\Levels\\level1.txt");
    levels.push_back("..\\BreakArk_Client\\Levels\\level2.txt");
    
    //Save brick images
    brickImages.push_back("..\\BreakArk_Client\\Images\\softbrick.bmp");
    brickImages.push_back("..\\BreakArk_Client\\Images\\mediumbrick.bmp");
    brickImages.push_back("..\\BreakArk_Client\\Images\\hardbrick.bmp");
    
    //Load first level
    FileToBricks(levels[level], x, y, Brick::BRICK_WIDTH, Brick::BRICK_HEIGHT, BRICKS_COLUMNS, FILE_DELIMITER);
}

Board::~Board() {
    Close();
}

void Board::Render(SDL_Renderer* renderer)
{
	std::vector<Brick*>::iterator it;
	for (it = bricks.begin(); it != bricks.end(); ++it)
	{
		if (!(*it)->IsDestroyed())
		{
			(*it)->Render(renderer);
		}
	}
}

void Board::FileToBricks(const std::string& fileName, int x, int y, const int offsetXBase, const int offsetYBase,
	const int bricksColumns, const char end)
{
	//Open file  
	std::ifstream ist(fileName.c_str());
	if (!ist)
	{
		std::cout << "error opening file" << std::endl;
		return;
	}

	ist.exceptions(ist.exceptions() | std::ios_base::badbit);

	int originalX = x;
	int offsetX = x;

	//Read file 
	int brickNum = 0;
	char del;

	int brickLimit = offsetXBase*bricksColumns+x+BRICKS_COLUMNS-1; // 3 = Max space when there are four bricks in a row
	int xBrickBefore = 0;
	int newXBrick = x;

	static const int DISPLACEMENT_OFFSET = 1;
        
        int id = 0;
	
		while (ist >> brickNum >> del)
		{
			if (brickNum)
			{
				Brick* brick = new Brick(x, y, (Brick::HARDNESS)brickNum, id);
				bricks.push_back(brick);
			}


			offsetX += offsetXBase + DISPLACEMENT_OFFSET;

			if (offsetX >= brickLimit)
			{
				offsetX = originalX;
				y += offsetYBase + 1;
			}

			x = offsetX;

			if (del == end)
			{
				return;
			}

			++id;
		}
}


void Board::InitiateBrickImages(SDL_Renderer* renderer)
{
    int hardness = 0;
    
	std::vector<Brick*>::iterator it;
	for (it = bricks.begin(); it != bricks.end(); ++it)
	{
		hardness = (*it)->GetHardness();
		if (!(*it)->InitTexture(renderer, brickImages[hardness - 1]))
		{
			std::cerr << "failed to InitTexture;" << std::endl;
			return;
		}
	}
}

void Board::DeleteBricks()
{
    std::vector<Brick*>::iterator it;
    for ( it = bricks.begin(); it != bricks.end();)
    {
      delete *it;  
      it = bricks.erase(it++);
   }
    
    bricks.erase(bricks.begin(), bricks.end());
}

bool Board::ChangeLevel(int newLevel)
{
    if (newLevel < MAX_LEVELS)
    {
        DeleteBricks();
        
        level = newLevel - 1;
        FileToBricks(levels[level], x, y, Brick::BRICK_WIDTH, Brick::BRICK_HEIGHT, BRICKS_COLUMNS, FILE_DELIMITER);
  
		return true;
    }
 
    return false;
}

bool Board::NextLevel()
{
    if (level < MAX_LEVELS)
    {
        ++level;
		DeleteBricks();
        FileToBricks(levels[level], x, y, Brick::BRICK_WIDTH, Brick::BRICK_HEIGHT, BRICKS_COLUMNS, FILE_DELIMITER);
        return true;
    }
    
    return false;
}

bool Board::NoBricksLeft() 
{
	std::vector<Brick*>::iterator it;
	for (it = bricks.begin(); it != bricks.end(); ++it)
	{
		if ( !(*it)->IsDestroyed() )
		{
			return false;
		}
	}

	return true;
}

void Board::DestroyBrick(int id)
{
	std::vector<Brick*>::iterator it;
	for (it = bricks.begin(); it != bricks.end(); ++it)
	{
		if ((*it)->GetID() == id)
		{
			(*it)->DestroyBrick();
			return;
		}
	}

}

void Board::DrawBricks(SDL_Renderer* renderer)
{
	std::vector<Brick*>::iterator it;
	for (it = bricks.begin(); it != bricks.end(); ++it)
	{
		if ((*it)->GetHardness())
		{
			(*it)->Render(renderer);
		}
	}

}
