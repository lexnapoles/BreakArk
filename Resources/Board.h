/* 
 * File:   Board.h
 * Author: EX350002
 *
 * Created on 29 de mayo de 2014, 14:00
 */

#ifndef BOARD_H
#define	BOARD_H

#include <fstream>
#include <vector>

#include "Brick.h"


class Board {
public:
	static const int MAX_LEVELS = 3;

    Board(int posX, int posY);
    ~Board();
    
    int GetLevel() { return level + 1; }
    std::vector<Brick*>& GetBricks() { return bricks; }
    
    bool NextLevel();
    
    void InitiateBrickImages(SDL_Renderer* renderer);
    
    bool ChangeLevel(int newLevel);
    
    bool NoBricksLeft();

	void DestroyBrick(int id);
    
    void Render(SDL_Renderer* renderer);
    
    void Close() { DeleteBricks(); }
    
private:
    static const char FILE_DELIMITER = ';';
    static const int BRICKS_COLUMNS = 4;
    int level;
    int x, y;
    
    std::vector<std::string> brickImages;
    std::vector<std::string> levels;
    std::vector<Brick*> bricks;
    
    void FileToBricks(const std::string& name, int x, int y, const int offsetXBase, const int offsetYBase,
                      const int bricksColumns,  const char end);
 
    void DrawBricks(SDL_Renderer* renderer);

    

    void DeleteBricks();
};

#endif	/* BOARD_H */

