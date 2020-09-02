#include <iostream>
#include "Server.h"
#include "..\Resources\Timer.h"
#include "..\Resources\SDLHelperFunctions.h"

int main(int argc, char *argv[])
{
   Timer timer;
	
	const int SCREEN_WIDTH = 700;
	const int SCREEN_HEIGHT = 700;
	const int SERVER_PORT = 3800;

	if (SDLNet_Init() < 0)
	{
		std::cerr << "Couldn't initiate SDL_NET" << std::endl;
		return -1;
	}

	Server server(SERVER_PORT, SCREEN_WIDTH, SCREEN_HEIGHT);


	if (!server.InitServer())
	{
		std::cerr << "Couldn't initiate server" << std::endl;
		int aux;
		std::cin >> aux;
		return -1;
	}
	
	double dtReal = 1.0 / 30.0;

	timer.Start();

	while (!server.RunGame(timer.GetTime(), dtReal));

	//Close systems
	return 0;
}