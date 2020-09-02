#ifndef GAME_H
#define	GAME_H

#include <SDL_net.h>
#include "Ball.h"
#include "Paddle.h"
#include "Board.h"
#include "Timer.h"

struct NetworkGameState
{
	Uint32 ballX;
	Uint32 ballY;
	Uint32 paddleX;
	Uint32 idQuantity;
	char bricksID[40];
	Uint32 order;
};

struct NetworkInput
{
	bool rightDown;
	bool rightUp;
	bool leftDown;
	bool leftUp;
	Uint32 order;
};


class Game
{
public:
	enum GameStates { INIT, PLAYING, PAUSED, WINNER, LOSER, END};
	enum GameOrders { NONE, NEXT, PAUSE, CONTINUE, EXIT, WIN, LOSE, LIFE };

    Game(int screenWidth, int screenHeight);
    ~Game();
  
	virtual size_t GetGameInfo(unsigned char* data) = 0;

	virtual void UpdateGame(unsigned char* data) = 0;

	void UpdateGameState(GameStates state);

	void ResetGameValues();
	
	void RestartGame();

	bool IsLevelFinished() { return board->NoBricksLeft(); }

	bool UserWon();
	bool UserLost() { return lifesLeft == 0; }

	GameStates GetState() { return gameState; }

	void SetOrder(GameOrders order) { this->order = order; }

	GameOrders GetOrder() { return order; }


	void ResetBall();	

protected:
	static const int MAX_LIFES = 2;
	static const int BALL_POSX = 200;
	static const int BALL_POSY = 500;
	static const int BALL_VELX = 300;
	static const int BALL_VELY = -200;
	static const int BOARD_POSX = 30;
	static const int BOARD_POSY = 100;

    
    Ball* ball;
    Paddle* paddle;
    Board* board;
	Timer gameTimer;

	GameStates gameState;
    GameOrders order;

	int lifesLeft;

    int screenWidth;
    int screenHeight;
  
	bool BallOutOfBounds();

    
    virtual void GameInfoToObjects(unsigned char* data) = 0;

	void InputToPaddleInput(const NetworkInput& userInput, PaddleInput& paddleInput);

	void ReduceLife() { --lifesLeft; }

	void CloseGame();


private:
	void ResetPaddle();
};

#endif	/* GAME_H */