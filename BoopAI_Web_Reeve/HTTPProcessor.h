#pragma once
#include <string>

#include "ServerSocket.h"
#include "Socket.h"

class HTTPListener : public SocketListener
{
public:
	HTTPListener(Socket* socket);
	virtual ~HTTPListener();
	void recv(string &s);
	void disconnected(const string &);
	Socket *getSocket();
	void connected();

private:
	Socket *client;
	string uid;
	static int numClients;
};

class HTTPServer : ServerSocketListener
{
public:
	HTTPServer();
	virtual ~HTTPServer() {}
	void shutdown(const string &);
	void awaitingClient(Socket *);
private:
	ServerSocket *server;
};
