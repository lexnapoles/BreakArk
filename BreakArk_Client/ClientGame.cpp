#include "ClientGame.h"

ClientGame::ClientGame(int screenWidth, int screenHeight, SDL_Renderer* renderer)
: Game(screenWidth, screenHeight)
{
	points = 0;

	pointsCounter = new Counter(20, 10);
	timeCounter = new Counter(screenWidth - 100, 10);
	lifeCounter = new Counter(screenWidth / 2 - 10, 10);

	wonTexture = new Texture();
	lostTexture = new Texture();
	pausedTexture = new Texture();

	LoadTextures(renderer);

	ball->InitTexture(renderer, "Images\\ball.bmp");
	paddle->InitTexture(renderer, "Images\\paddle.bmp");
}

ClientGame::~ClientGame()
{
	CloseClientGame();
}

void ClientGame::CloseClientGame()
{
	delete pointsCounter;
	pointsCounter = nullptr;

	delete timeCounter;
	timeCounter = nullptr;

	delete wonTexture;
	wonTexture = nullptr;

	delete lostTexture;
	lostTexture = nullptr;

	delete pausedTexture;
	pausedTexture = nullptr;
}

bool ClientGame::GetInput()
{
   if (inputHandler.HandleEvents())
    {
        return true;
    }
    return false;
}

void ClientGame::ClearScreen(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);
}


void ClientGame::UpdateGame(unsigned char* data)
{
	 GameInfoToObjects(data); 

	 if (lifesLeft == 0)
	 {
		 UpdateGameState(GameStates::LOSER);
	 }
}


 void ClientGame::GameInfoToObjects(unsigned char* data)
 {
	 NetworkGameState state;

	 memcpy(&state, data, sizeof(NetworkGameState));

	 ball->SetPosX(SDL_SwapBE32(state.ballX));
	 ball->SetPosY(SDL_SwapBE32(state.ballY));
	 
	 paddle->SetPosX(SDL_SwapBE32(state.paddleX));

	 Uint32 idQuant = SDL_SwapBE32(state.idQuantity);

	 points += idQuant*POINTS_MULTIPIER;

	 if (idQuant)
	 {
		 Uint32 aux;
		 int i = 0;
		 int displacement = 0;

		 for (int j = 0; j < idQuant; ++j)
		 {
			 
			 memcpy(&aux, state.bricksID + displacement, sizeof(int));
			 board->DestroyBrick(SDL_SwapBE32(aux));

			 ++i;
			 displacement = i*sizeof(int);
		 }
	 }

	 order = (GameOrders)SDL_SwapBE32(state.order);
 }

 void ClientGame::RenderGame(SDL_Renderer* renderer)
 {
	 ClearScreen(renderer);

	 switch (gameState)
	 {
	 case INIT: case PLAYING:
		 RenderCounters(renderer);
		 ball->Render(renderer);
		 paddle->Render(renderer);
		 board->Render(renderer);
		 
		 break;

	 case WINNER:
		 wonTexture->Render(0, 0, renderer);
		 break;

	 case LOSER:
		 lostTexture->Render(0, 0, renderer);
		 break;

	 case PAUSED:
		 pausedTexture->Render(0, 0, renderer);

		 break;
	 }

	 SDL_RenderPresent(renderer);
 }


 void ClientGame::RenderCounters(SDL_Renderer* renderer)
 {
	 pointsCounter->UpdateCounter(points, "Points: " , renderer);
	 timeCounter->UpdateCounter((int)gameTimer.GetTime()/1000, "Time: ", renderer);
	 lifeCounter->UpdateCounter(lifesLeft, "Lifes: ", renderer);
	 
	 pointsCounter->Render(renderer);
	 timeCounter->Render(renderer);
	 lifeCounter->Render(renderer);
 }

 void ClientGame::InputToNetworkInput(const UserInput userInput, NetworkInput& networkInput)
{
	 networkInput.leftDown = SDL_SwapBE32((Uint32)userInput.leftDown);
	 networkInput.leftUp = SDL_SwapBE32((Uint32)userInput.leftUp);
	 networkInput.rightDown = SDL_SwapBE32((Uint32)userInput.rightDown);
	 networkInput.rightUp = SDL_SwapBE32((Uint32)userInput.rightUp);
	 networkInput.order = SDL_SwapBE32((Uint32)order);
}

 size_t ClientGame::GetGameInfo(unsigned char* data)
{
	NetworkInput networkInput;
	InputToNetworkInput(inputHandler.GetInput(), networkInput);
	
	memcpy(data, &networkInput, sizeof(NetworkInput));

	return sizeof(NetworkInput);
}

void ClientGame::NextLevel(SDL_Renderer* renderer)
{
	//Must restart lifes, timer, and position of ball and paddle
	lifesLeft = MAX_LIFES;
	
	gameTimer.Start();

	board->NextLevel();
	board->InitiateBrickImages(renderer);
}

bool ClientGame::IsExit()
{
	if (inputHandler.GetInput().quit)
	{
		SetOrder(Game::GameOrders::EXIT);
		return true;
	}

	return false;
}

void ClientGame::IsESC()
{
	if (inputHandler.GetInput().esc)
	{
		if (gameState == PLAYING)
		{
			UpdateGameState(PAUSED);
			SetOrder(PAUSE);
		}
		else if (gameState == PAUSED)
		{
			UpdateGameState(PLAYING);
			SetOrder(CONTINUE);
		}
		else if( gameState == WINNER || gameState == LOSER)
		{
			UpdateGameState(END);
			SetOrder(EXIT);
		}
	}
}

void ClientGame::IsEnter(SDL_Renderer* renderer)
{
	if (inputHandler.GetInput().enter && (gameState == WINNER || gameState == LOSER))
	{
			order = CONTINUE;
			UpdateGameState(INIT);

			points = 0;
			board->InitiateBrickImages(renderer);
	}
}

void ClientGame::Comply(SDL_Renderer* renderer)
{
	switch (order)
	{
	case LIFE:
		ResetBall();
		ReduceLife();
		break;
	case NEXT:
		SDL_Delay(50);
		NextLevel(renderer);
		break;
	case WIN:
		UpdateGameState(WINNER);
		break;
	case LOSE:
		UpdateGameState(LOSER);
		break;
	}
}

void ClientGame::LoadTextures(SDL_Renderer* renderer)
{
	wonTexture->LoadFromFile("Images\\won.bmp", renderer);
	lostTexture->LoadFromFile("Images\\lost.bmp", renderer);
	pausedTexture->LoadFromFile("Images\\paused.bmp", renderer);
}
