#include "..\Resources\Game.h"
#include "..\Resources\CollisionSystem.h"
#include <vector>

class ServerGame : public Game
{
public:
	ServerGame(int screenWidth, int screenHeight);	
	~ServerGame();

	void UpdateSimulation(double t, double dt);

	size_t GetGameInfo(unsigned char* data);
	
	void UpdateGame(unsigned char* data) { GameInfoToObjects(data); }

	void NextLevel();

	void Comply();

private:
	std::vector<int> bricksDestroyed;
	CollisionSystem collisionSystem;
     
    void GameInfoToObjects(unsigned char* data);

};