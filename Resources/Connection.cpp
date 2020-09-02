#include "Connection.h"


Connection::Connection(int protocolId, float timeout)
{
	this->protocolId = protocolId;
	this->timeout = timeout;
	mode = None;
	running = false;
	ClearData();
}


Connection::~Connection()
{
	if (running)
		Stop();
}

bool Connection::Start(int port)
{
	if (running)
	{
		std::cerr << "connection is already running" << std::endl;
		return false;
	}
	else
	{
		if (!socket.Open(port))
		{
			return false;
		}
		
		running = true;
		return true;
	}
}

void Connection::Stop()
{
	if (!running)
	{
		std::cerr << "connection is already stopped" << std::endl;
		return;
	}

	ClearData();
	socket.Close();
	running = false;
}

void Connection::Listen()
{
	ClearData();
	mode = Server;
	state = Listening;
}

void Connection::Connect(const IPaddress &address)
{
	ClearData();
	mode = Client;
	state = Connecting;
	this->address = address;
}

void Connection::Update(float deltaTime)
{
	if (!running)
	{
		std::cerr << "connection is not running" << std::endl;
		return;
	}

	timeoutAccumulator += deltaTime;

	if (timeoutAccumulator > timeout)
	{
		if (state == Connecting)
		{
			std::cerr << "connect timed out" << std::endl;
			ClearData();
			state = ConnectFail;
		}
		else if (state == Connected)
		{
			std::cerr << "connection timed out" << std::endl;
			ClearData();
		}
	}
}

bool Connection::SendPacket(const unsigned char data[], size_t size)
{

	if (!running)
	{
		std::cerr << "connection is not running" << std::endl;
		return false;
	}

	if (address.host == 0)
	{
		std::cerr << "address host is empty";
		return false;
	}
	
	//Insert the protocolId + data into the packet data
	unsigned char packet[PACKET_SIZE];
	Uint32 protocolIdAux = SDL_SwapBE32(protocolId);

	memcpy(packet, &protocolIdAux, sizeof(Uint32));
	memcpy(packet + sizeof(Uint32), data, size);

	return socket.Send(address, packet, sizeof(Uint32)+size);
}


int Connection::ReceivePacket(unsigned char data[])
{
	if (!running)
	{
		std::cerr << "connection is not running" << std::endl;
		return 0;
	}

	IPaddress sender;
	unsigned char packet[PACKET_SIZE];

	size_t bytes = socket.Receive(sender, packet);
	
	//If packet has no data or only the protocolId return 0
	if (bytes <= sizeof(Uint32))
	{
		return 0;
	}

	Uint32 protocolIdAux = 0;
	memcpy(&protocolIdAux, packet, sizeof(Uint32));
	
	if (protocolId != SDL_SwapBE32(protocolIdAux))
	{
		return 0;
	}

	//If packet comes from a client the server does not know anything about then server connects with the client (just one client at the moment)
	if (mode == Server && !IsConnected())
	{
		state = Connected;
		address = sender;
	}

	if (sender.host == address.host && sender.port == address.port)
	{
		if (mode == Client && state == Connecting)
		{
			std::cout << "client completes connection with server" << std::endl;
			state = Connected;
		}
		timeoutAccumulator = 0.0f;
		memcpy(data, packet + sizeof(Uint32), bytes - sizeof(Uint32));

		return bytes - sizeof(Uint32);
	}

	return 0;
}

void Connection::ClearData()
{
		state = Disconnected;
		timeoutAccumulator = 0.0f;
		address.host = 0;
		address.port = 0;
}