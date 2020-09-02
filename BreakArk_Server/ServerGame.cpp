#include "ServerGame.h"


ServerGame::ServerGame(int screenWidth, int screenHeight)
           : Game(screenWidth, screenHeight)
{
}

ServerGame::~ServerGame()
{
}


void ServerGame::GameInfoToObjects(unsigned char* data)
{
	//Pass the data from the client to the objects in server
	NetworkInput networkInput;
	memcpy(&networkInput, data, sizeof(NetworkInput));
   
	PaddleInput pI;
	InputToPaddleInput(networkInput, pI);

	paddle->HandleInput(pI);

	order = (GameOrders)SDL_SwapBE32(networkInput.order);
}


void ServerGame::UpdateSimulation(double t, double dt)
{
	// Move objects, detect and react to collisions 
	
	ball->Move(t, dt);
	paddle->Move(t, dt);
	
	bricksDestroyed.clear();
	collisionSystem.UpdateCollisions(*ball, *paddle, board->GetBricks(), screenWidth, screenHeight, t, dt, bricksDestroyed);

	if (BallOutOfBounds())
	{
		ResetBall();
		ReduceLife();

		order = LIFE;
	}
}

size_t ServerGame::GetGameInfo(unsigned char* data)
{
	//Fill NetworkGameState structure in Big Endian (network byte order)
	NetworkGameState state;

	state.ballX = SDL_SwapBE32((Uint32)ball->GetPosX());
	state.ballY = SDL_SwapBE32((Uint32)ball->GetPosY());
	state.paddleX = SDL_SwapBE32((Uint32)paddle->GetPosX());
	state.idQuantity = SDL_SwapBE32((Uint32)bricksDestroyed.size());
	state.order = SDL_SwapBE32((Uint32)order);
	
	Uint32 brickID;
	int displacement;
	int i = 1;

	if (state.idQuantity)
	{
		displacement = 0;

		std::vector<int>::iterator it;
		for (it = bricksDestroyed.begin(); it != bricksDestroyed.end(); ++it)
		{
			brickID = SDL_SwapBE32((Uint32)*it);
			memcpy(state.bricksID + displacement, &brickID, sizeof(Uint32));
			displacement = i*sizeof(Uint32);
			++i;
		}
	}
	else
	{
		state.bricksID[0] = 0;
	}

	memcpy(data, &state, sizeof(NetworkGameState));

	return sizeof(NetworkGameState);
}

void ServerGame::NextLevel()
{
	lifesLeft = MAX_LIFES;

	ResetGameValues();

	board->NextLevel();
}

void ServerGame::Comply()
{
	switch (order)
	{
	case PAUSE:

		UpdateGameState(PAUSED);
		break;

	case CONTINUE:

		if (gameState == PAUSED)
		{
			UpdateGameState(PLAYING);
		}
		else if (gameState == WINNER || gameState == LOSER)
		{
			UpdateGameState(INIT);
		}
		break;

	case EXIT:

		UpdateGameState(END);
		break;
	}
}