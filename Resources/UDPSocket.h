//UDP Socket class to encapsulate all the functions and variable related to it
//in order to make it easier to send or receive messages (without us having 
//to know the file descriptor, ports, etc.

#include <SDL_net.h>
#include <cstring>
#include <iostream>

class UDPSocket
{
public:
	UDPSocket();
	~UDPSocket();

	bool Open(int port);

	bool Send(const IPaddress &destination, const void * data, size_t size); //Send packet to destination IP
	size_t Receive(IPaddress &sender, void * data);  //Receive packet.

	void Close(); //Close the socket

private:
	static const int PACKET_SIZE = 512;

	UDPsocket socket;
	UDPpacket* packet;

	
	bool AllocPacket(UDPpacket **p);
	
};
