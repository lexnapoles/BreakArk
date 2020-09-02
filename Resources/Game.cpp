#include "Game.h"

Game::Game(int screenWidth, int screenHeight)
{
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    
	ball = new Ball(BALL_POSX, BALL_POSY, BALL_VELX, BALL_VELY);
	paddle = new Paddle(screenWidth / 2 - Paddle::PADDLE_WIDTH / 2, screenHeight - Paddle::PADDLE_HEIGHT);
	board = new Board(BOARD_POSX, BOARD_POSY);

	lifesLeft = MAX_LIFES;

    gameState = INIT;
	order = NONE;
}

Game::~Game()
{
	CloseGame();
}

bool Game::UserWon()
{
	if (board->NoBricksLeft() && board->GetLevel() == Board::MAX_LEVELS)
	{
		return true;
	}

	return false;
}

void Game::CloseGame()
{
	delete ball;
	ball = nullptr;

	delete paddle;
	paddle = nullptr;

	delete board;
	board = nullptr;
}

void Game::ResetBall()
{
	ball->SetPosX(BALL_POSX);
	ball->SetPosY(BALL_POSY);
	ball->SetVelX(BALL_VELX);
	ball->SetVelY(BALL_VELY);
}

void Game::ResetPaddle()
{
	paddle->SetPosX(screenWidth / 2 - Paddle::PADDLE_WIDTH / 2);
	paddle->SetPosY(screenHeight - Paddle::PADDLE_HEIGHT);
}

void Game::ResetGameValues()
{
	ResetBall();
	ResetPaddle();
}

void Game::RestartGame()
{
	lifesLeft = MAX_LIFES;

	ResetGameValues();
	board->ChangeLevel(1);
}
void Game::UpdateGameState(GameStates state)
{
	// INIT -> PLAYING
	if (gameState == INIT && state == PLAYING)
	{
		gameState = PLAYING;
		gameTimer.Start();
	}

	// PLAYING -> PAUSED
	else if (gameState == PLAYING && state == PAUSED)
	{
		gameState = PAUSED;
		gameTimer.Pause();
	}

	// PAUSED -> PLAYING
	else if (gameState == PAUSED && state == PLAYING)
	{
		gameState = PLAYING;
		gameTimer.UnPause();
	}

	// PLAYING -> WINNER || PLAYING -> LOSER
	else if (gameState == PLAYING && state == WINNER || state == LOSER)
	{
		gameState = state;
		gameTimer.Stop();
	}
	
	//  WINNER || LOSER  -> INIT
	else if (gameState == WINNER || gameState == LOSER && state == INIT)
	{
		gameState = INIT;
		RestartGame();

		gameTimer.Stop();
	}

	//  WINNER || LOSER  -> END
	else if (gameState == WINNER || gameState == LOSER && state == END)
	{
		gameState = END;
		gameTimer.Stop();
	}
}

bool Game::BallOutOfBounds()
{
	return ball->GetPosY() + ball->GetCollider().r > screenHeight;
}

void Game::InputToPaddleInput(const NetworkInput& userInput, PaddleInput& paddleInput)
{
		paddleInput.leftDown = SDL_SwapBE32((Uint32)userInput.leftDown);
		paddleInput.leftUp = SDL_SwapBE32((Uint32)userInput.leftUp);
		paddleInput.rightDown = SDL_SwapBE32((Uint32)userInput.rightDown);
		paddleInput.rigthUp = SDL_SwapBE32((Uint32)userInput.rightUp);
}

