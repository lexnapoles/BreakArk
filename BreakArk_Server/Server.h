#include <SDL_net.h>
#include "..\Resources\Connection.h"
#include "ServerGame.h"


class Server
{
public:
	Server(int serverPort, int screenWidth, int screenHeight);
	~Server();

	bool RunGame(double t, double dt);

	bool InitServer();

	void CloseServer();

private:
	Connection* connection;
	ServerGame* serverGame;

	static const int PROTOCOL_ID = 0x99887766;
	static const int TIMEOUT = 5000;

	int serverPort;

	void SendGameInfoToClient();

	bool RecvGameInfoFromClient(unsigned char* data);
};

