#include "Client.h"


Client::Client(int clientPort, SDL_Renderer* renderer, int screenWidth, int screenHeight)
{
	this->clientPort = clientPort;

	connection = new Connection(PROTOCOL_ID, TIMEOUT);
	clientGame = new ClientGame(screenWidth, screenHeight, renderer);
}

Client::~Client()
{
	CloseClient();
}

void Client::CloseClient()
{
	delete connection;
	connection = nullptr;

	delete clientGame;
	clientGame = nullptr;
}
void Client::SendGameInfoToServer()
{
	unsigned char data[512];

	int size = clientGame->GetGameInfo(data);

	connection->SendPacket(data, size);
}

bool Client::RecvGameInfoFromServer(unsigned char* data)
{
	if (connection->ReceivePacket(data))
	{
		return true;
	}

	return false;
}

bool Client::InitClient(std::string serverIP, int serverPort)
{
	if (connection->Start(clientPort))
	{

		if (SDLNet_ResolveHost(&serverAdd, serverIP.c_str(), serverPort) < 0)
		{
			std::cerr << "fallo al resolver host";
		}

		connection->Connect(serverAdd);

		return true;
	}
	
	return false;
}


void Client::SyncWithServer()
{
	//Send a message to the server in order for it to connect with the client.
	unsigned char syn[] = "SYN";
	connection->SendPacket(syn, strlen((char*)syn));

	bool connected = false;

	if (!connected && connection->IsConnected())
	{
		connected = true;
		std::cerr << "client connected to server" << std::endl;
	}

	else if (!connected && connection->ConnectFailed())
	{
		std::cerr << "connection to server failed" << std::endl;
	}

}
bool Client::RunGame(SDL_Renderer* renderer, double dt)
{
	double t = 0;

	unsigned char data[512];
	bool renderScreen = true;
	bool connected = false;

	while (!clientGame->IsExit() && t < dt)
	{
	  	
		if (clientGame->GetInput())
		{
			//Clear order
			clientGame->SetOrder(Game::GameOrders::NONE);
		
			clientGame->IsESC();

			clientGame->IsEnter(renderer);

			// Send data to server when state is different that INIT or if client is restarting from a winner/loser screen
			if (clientGame->GetState() != Game::GameStates::INIT || clientGame->GetState() == Game::GameStates::INIT && clientGame->GetOrder() == Game::GameOrders::CONTINUE)
			{
				SendGameInfoToServer();
			}
		}
		
		switch (clientGame->GetState())
		{
		case Game::GameStates::INIT:

			clientGame->RenderGame(renderer);
			clientGame->UpdateGameState(Game::GameStates::PLAYING);
			break;

		case Game::GameStates::PLAYING:

			if (!renderScreen)
			{
				//Clear renderScreen
				renderScreen = true;
			}

			data[0] = 0;
			if (RecvGameInfoFromServer(data))
			{
				clientGame->UpdateGame(data);
				clientGame->Comply(renderer);
				clientGame->RenderGame(renderer);
			}

			break;

		case Game::GameStates::PAUSED:

		// Render the paused screen just once in a row
			if (renderScreen)
			{
				clientGame->RenderGame(renderer);
				renderScreen = false;
			}
			break;

		case Game::GameStates::WINNER: case  Game::GameStates::LOSER:
			
			// Render the winner or loser screen just once in a row
			if (renderScreen)
			{
				clientGame->RenderGame(renderer);
				renderScreen = false;
			}
			break;

		case Game::GameStates::END:
			return true;
		}
		
			t += dt;
	}

	if (clientGame->IsExit())
	{
		//Send packet to Server with order = EXIT
		SendGameInfoToServer();
		return true;
	}

	//Update connection's timeout if the game isn't waiting for player's input in the winner/loser/paused screen (not doing this times out the connection while waiting)
	if (clientGame->GetState() != Game::GameStates::WINNER && clientGame->GetState() != Game::GameStates::LOSER &&  clientGame->GetState() != Game::GameStates::PAUSED)
	{
		connection->Update(dt);
	}

	return false;
}

