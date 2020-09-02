#include <SDL.h>

#include <iostream>

#include "Client.h"
#include "..\BreakArk_Server\Server.h"
#include "..\Resources\Timer.h"
#include "..\Resources\SDLHelperFunctions.h"

int main(int argc, char *argv[])
{
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	
	const int SCREEN_WIDTH = 700;
	const int SCREEN_HEIGHT = 700;
	const int CLIENT_PORT = 4001;
	const int SERVER_ON_CLIENT_PORT = 3999;
	const int REMOTE_SERVER_PORT = 3800;

	Timer timer;
	
	if (!InitSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT))
	{
		std::cerr << "Couldn't initiate SDL_NET" << std::endl;
		return -1;
	}

	Client client(CLIENT_PORT, renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	Server localServer(SERVER_ON_CLIENT_PORT, SCREEN_WIDTH, SCREEN_HEIGHT);

	//Localhost or remote server
	bool local = false;
	int serverPort = 0;

	if (argc)
	{
		std::string serverIP = "localhost";

		if (!strcmp(argv[1], serverIP.c_str()))
		{
			local = true;	
			serverPort = SERVER_ON_CLIENT_PORT;

			if (!localServer.InitServer())
			{
				std::cerr << "Couldn't initiate server" << std::endl;
				return -1;
			}

		}
		else
		{
			serverIP = argv[1];
			serverPort = REMOTE_SERVER_PORT;
		}

		if (!client.InitClient(serverIP, serverPort))
		{
			std::cerr << "Couldn't initiate client" << std::endl;
			int aux;
			std::cin >> aux;
			return -1;
		}

		client.SyncWithServer();
		client.InitGame(renderer);
	}
	else
	{
		std::cerr << "Not enough arguments, game needs server IP (localhost or Destination IP)" << std::endl;
		int aux;
		std::cin >> aux;
		return -1;
	}

	double tBegin, dtServer, dtReal;
	bool quit = false;

	dtReal = 1.0 / 60.0;

	if (local)
	{
		dtServer = 0.0;

		timer.Start();
		tBegin = timer.GetTime();

		while (!quit)
		{
			//Server runs at 33,33ms intervals (30 FPS)
			dtServer += dtReal;

			if (dtServer >= 0.033)
			{
				localServer.RunGame(timer.GetTime(), 0.033);
				dtServer -= 0.033;
			}

			//Run client at maximum frame rate (60 FPS)
			quit = client.RunGame(renderer, dtReal);

			double tEnd = timer.GetTime();
			dtReal = tEnd - tBegin;
			tBegin = tEnd;
		}
	}

	else
	{
		while (!client.RunGame(renderer, dtReal));
	}
	
	//Close systems
	client.CloseClient();
	CloseSDL(window, renderer);
	TTF_Quit();

	return 0;
}