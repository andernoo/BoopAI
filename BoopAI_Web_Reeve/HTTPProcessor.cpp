#include "HTTPProcessor.h"
#include <fstream>
#include "ServerSocket.h"
#include "Socket.h"
#include "SocketHandler.h"

#include <stdlib.h>
#include <string>

#include "Utils.h"
#include "StringTokenizer.h"
#include "Stream.h"
#include "websocket.h"
#include <iostream>

using namespace std;

string templateContents;

HTTPServer::HTTPServer()
{
	server = new ServerSocket(2213);
	SocketHandler::addSocket("Web Server", server);

	server->setServerListener(this);
	if(server->init())
	{
		char str[1024];
		sprintf(str, "HTTPServer-> Starting up server (listening on port %d)\n", 2213);
		std::cout << str << std::endl;
	}
}

void HTTPServer::shutdown(const string &msg)
{
	cout << "HTTPServer-> Shutting down server: " << msg << endl;
	string err = "HTTPServer-> Shutting down server: " + msg + "\n";
	std::cout << err.c_str() << std::endl;
}

void HTTPServer::awaitingClient(Socket* socket)
{
	socket->setListener(new HTTPListener(socket));
}

HTTPListener::HTTPListener(Socket *s)
{
	numClients = 0;
	client = s;
	int n = ++numClients;
	while(n > 0)
	{
		char ch = (char)(n % 10) + '0';
		uid = ch + uid;
		n /= 10;
	}
	uid = "Web Client " + uid;
	SocketHandler::addSocket(uid, client);
}

HTTPListener::~HTTPListener()
{
}

void HTTPListener::disconnected(const string &)
{
	//	Needed here as well, for cases when recv() doesn't get called...
	SocketHandler::removeSocket(uid);
	--HTTPListener::numClients;
}

Socket * HTTPListener::getSocket()
{
	return client;
}

void HTTPListener::connected()
{
	cout << "HTTPListener-> Client connected" << endl;
}

int HTTPListener::numClients = 0;

void HTTPListener::recv(string &s)
{
	if(WebSocketServer::isWS(client->getSD()))
		s = WebSocketServer::decode(s.c_str());
	std::cout << client->getPeerName() << " says: " << s << std::endl;
	int sd = client->getSD();
	string response = s;

	WebSocketServer::sendMessage(sd, response);
}