#include "Server.h"


Server::Server(int serverPort, int screenWidth, int screenHeight)
{
	this->serverPort = serverPort;

	connection = new Connection(PROTOCOL_ID, TIMEOUT);
	serverGame = new ServerGame(screenWidth, screenHeight);
}

Server::~Server()
{
	CloseServer();
}

void Server::CloseServer()
{
	delete connection;
	connection = nullptr;

	delete serverGame;
	serverGame = nullptr;
}

void Server::SendGameInfoToClient()
{
	unsigned char data[512];
	
	size_t size = serverGame->GetGameInfo(data);

	connection->SendPacket(data, size);
}

bool Server::RecvGameInfoFromClient(unsigned char* data)
{
	//Just one client at the moment
	if (connection->ReceivePacket(data))
	{
		return true;
	}

	return false;
}

bool Server::InitServer()
{
	//Start socket and listening for clients
	if (connection->Start(serverPort))
	{	   
		connection->Listen();
		std::cout << "server open, waiting for connection" << std::endl;

		return true;
	}

	return false;
}

bool Server::RunGame(double t, double dt)
{
	unsigned char data[512];

	static bool synMessage = true;
	double auxT = 0;

	while (auxT < dt)
	{
		//Clear order
		serverGame->SetOrder(Game::GameOrders::NONE);

		//Get input from client
		if (RecvGameInfoFromClient(data))
		{
			if (serverGame->GetState() == Game::GameStates::INIT)
			{
				serverGame->UpdateGameState(Game::GameStates::PLAYING);
			}

			if (connection->IsConnected())
			{
				//Don't update game at SYN message 
				if (!synMessage)
				{
					serverGame->UpdateGame(data);
					serverGame->Comply();

				}
				else
				{
					synMessage = false;
				}
			}
		}

		switch (serverGame->GetState())
		{
		case Game::GameStates::INIT: case Game::GameStates::PLAYING:

			if (serverGame->UserWon())
			{
				serverGame->SetOrder(Game::GameOrders::WIN);
				serverGame->UpdateGameState(Game::GameStates::WINNER);
			}
			else if (serverGame->UserLost())
			{
				serverGame->SetOrder(Game::GameOrders::LOSE);
				serverGame->UpdateGameState(Game::GameStates::LOSER);
			}
			else if (serverGame->IsLevelFinished())
			{
				serverGame->NextLevel();
				serverGame->SetOrder(Game::GameOrders::NEXT);
			}


			if (connection->IsConnected())
			{
				serverGame->UpdateSimulation(t, dt);
				SendGameInfoToClient();
			}
			
			break;

		case Game::GameStates::PAUSED:
			break;

		case Game::GameStates::WINNER: case  Game::GameStates::LOSER:

			//Waiting for a CONTINUE order from the client to restart the game
			if (serverGame->GetOrder() == Game::GameOrders::CONTINUE)
			{
				serverGame->RestartGame();
			}
			break;

		case Game::GameStates::END:
			return true;
		}

		auxT += dt;

	}

	// Update connection's timeout if the game isn't waiting for the client's order 
	// (client is in winner/loser/paused screen waiting for input to restart or exit the game)
	if (serverGame->GetState() != Game::GameStates::WINNER && serverGame->GetState() != Game::GameStates::LOSER && serverGame->GetState() != Game::GameStates::PAUSED)
	{
		connection->Update(dt);
	}

	return false;
}

