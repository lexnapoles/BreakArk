#include "UDPSocket.h"

UDPSocket::UDPSocket()
{
	socket = nullptr;
	packet = nullptr;
}

UDPSocket::~UDPSocket()
{
	Close();
}


bool UDPSocket::Open(int port)
{
	if (!(socket = SDLNet_UDP_Open(port)) || !AllocPacket(&packet))
	{
		return false;
	}

	return true;
}


bool UDPSocket::Send(const IPaddress &destination, const void * data, size_t size)
{
	packet->data[0] = 0;

	//Fill packet
	memcpy((char*)packet->data, data, size);
	packet->address.host = destination.host;
	packet->address.port = destination.port;
	packet->len = size+1;

	//Send packet. Return false if the packet cannot be sent;
	if (!SDLNet_UDP_Send(socket, -1, packet))
	{
		return false;
	}

	return true;
}

size_t UDPSocket::Receive(IPaddress& sender, void * data)
{
	if (socket == nullptr)
	{
		return 0;
	}

	packet->data[0] = 0;

	if (SDLNet_UDP_Recv(socket, packet))
	{
		sender.host = packet->address.host;
		sender.port = packet->address.port;

		memcpy(data, (char*)packet->data, packet->len);

		return packet->len;
	}
	
	return 0;
}

bool UDPSocket::AllocPacket(UDPpacket **p)
{
	//Allocate memory for the packet
	*p = SDLNet_AllocPacket(PACKET_SIZE);
	if (*p == nullptr)
	{
		return false;
	}
	return true;
}

void UDPSocket::Close()
{
	//Close the socket
	SDLNet_UDP_Close(socket);
	socket = nullptr;

	//Free packet
	SDLNet_FreePacket(packet);
	packet = nullptr;
}






