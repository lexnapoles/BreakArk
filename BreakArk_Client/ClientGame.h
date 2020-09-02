
#ifndef CLIENTGAME_H
#define	CLIENTGAME_H

#include "..\Resources\Game.h"
#include "..\Resources\InputHandler.h"
#include "..\Resources\Texture.h"
#include "Counter.h"

#include <SDL.h>

class ClientGame : public Game
{
public:
	ClientGame(int screenWidth, int screenHeight, SDL_Renderer* renderer);
	~ClientGame();

	bool GetInput();

	void RenderGame(SDL_Renderer* renderer);

	void UpdateGame(unsigned char* data); 

	size_t GetGameInfo(unsigned char* data);

	bool IsExit();

	void IsESC();

	void IsEnter(SDL_Renderer* renderer);

	void CloseClientGame();

	void NextLevel(SDL_Renderer* renderer);

	//Comply to the orders the server has sent
	void Comply(SDL_Renderer* renderer);
	
	//Load board images
	void LoadImages(SDL_Renderer* renderer) { board->InitiateBrickImages(renderer); }

private:
    InputHandler inputHandler;
	Counter* pointsCounter;
	Counter* timeCounter;
	Counter* lifeCounter;
	
	Texture* wonTexture;
	Texture* lostTexture;
	Texture* pausedTexture;

	static const int POINTS_MULTIPIER = 100;

	int points;

	//Information received from the server to the objects
    void GameInfoToObjects(unsigned char* data);
    
    void InputToNetworkInput(const UserInput userInput, NetworkInput& networkInput);

	void RenderCounters(SDL_Renderer* renderer);

	void LoadTextures(SDL_Renderer* renderer);

	void ClearScreen(SDL_Renderer* renderer);
};

#endif	/* CLIENTGAME_H */