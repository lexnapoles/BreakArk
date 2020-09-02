#ifndef CLIENT_H
#define	CLIENT_H

#include <SDL_net.h>
#include <iostream>
#include <string>

#include "..\Resources\Connection.h"
#include "ClientGame.h"

class Client
{
public:
	Client(int clientPort, SDL_Renderer* renderer, int screenWidth, int screenHeight);
	~Client();

	bool RunGame(SDL_Renderer* renderer, double dt);
	
	void ConnectToServer();
	
	bool InitClient(std::string serverIP, int serverPort);
	
	void InitGame(SDL_Renderer* renderer) { clientGame->LoadImages(renderer); }

	void CloseClient();

	void SyncWithServer();

private:
	Connection* connection;
	ClientGame* clientGame;

	IPaddress serverAdd;

	static const int PROTOCOL_ID = 0x99887766;
	static const int TIMEOUT = 5000;
	int clientPort;

	bool RecvGameInfoFromServer(unsigned char* data);

	void SendGameInfoToServer();
};

#endif	/* CLIENT_H */
