
#ifndef CONNECTION_H
#define	CONNECTION_H


#include "UDPSocket.h"
#include <SDL_net.h>
#include <stdlib.h> 

class Connection
{
public:
	Connection(int protocolId, float timeout);
	~Connection();

	enum Mode
	{
		None,
		Client,
		Server
	};

	bool Start(int port);
	void Stop();
	void Listen();
	void Connect(const IPaddress &address);

	bool IsConnecting() { return state == Connecting; }
	bool ConnectFailed() {	return state == ConnectFail; }
	bool IsConnected() { return state == Connected; }
	bool IsListening() { return state == Listening; }
	
	Mode GetMode() { return mode; }
	
	void Update(float deltaTime);

	bool SendPacket(const unsigned char data[], size_t size);
	int ReceivePacket(unsigned char data[]);

protected:

	void ClearData();

private:
	enum State
	{
		Disconnected,
		Listening,
		Connecting,
		ConnectFail,
		Connected
	};

	static const int PACKET_SIZE = 256;
	Uint32 protocolId;
	float timeout;

	bool running;
	Mode mode;
	State state;
	UDPSocket socket;
	IPaddress address;
	float timeoutAccumulator;
};

#endif	/* CONNECTION_H */