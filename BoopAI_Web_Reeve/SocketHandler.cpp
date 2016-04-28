#include "SocketHandler.h"
#include <iostream>

#ifdef _WIN32
#include <winsock2.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netdb.h>
#endif

#include <stdio.h>

#include "Socket.h"
#include "websocket.h"
#include "TimeKeeper.h"

using namespace std;

bool SocketHandler::alreadyRunning = false;
map<string, Socket *> SocketHandler::sockets;

void SocketHandler::runLoop()
{
	std::cout << "SocketHandler-> Starting Main Loop" << std::endl;
	if(alreadyRunning)
	{
		return;
	}
	alreadyRunning = true;

	Socket *sock;
	int socket, result;
	while(!sockets.empty())
	{
		//	Do timing stuff..
		timer->processPending();

		fd_set input_sockets;

		FD_ZERO(&input_sockets);
		for(auto s = sockets.begin(); s != sockets.end(); ++s)
		{
			sock = (*s).second;
			string name = (*s).first;
			if(sock != NULL)
			{
				socket = sock->getSD();
			} else
			{
				socket = -1;
			}
			if(socket != -1)
			{
				FD_SET(socket, &input_sockets);
			}
		}

		struct timeval timeout;

		timeout.tv_sec = 2;
		timeout.tv_usec = 500 * 1000;

#ifdef WIN32
		result = select(FD_SETSIZE, (fd_set FAR *)&input_sockets, NULL, NULL, (const struct timeval FAR *)&timeout);
#else
		result = select(FD_SETSIZE, &input_sockets, NULL, NULL, &timeout);
#endif

		switch(result)
		{
		case 0:		//	Timeout on the sockets
			continue;
		case -1:	//	Select error, so stop
			perror("select");
			alreadyRunning = false;
			return;
		}

		for(auto itrb = sockets.begin(); itrb != sockets.end(); ++itrb)
		{
			string name = (*itrb).first;
			sock = (*itrb).second;
			if(sock != NULL)
			{
				socket = sock->getSD();
			} else
			{
				socket = -1;
			}

			if(socket != -1 && FD_ISSET(socket, &input_sockets))
			{
				sock->process();
			}
		}
	}
	alreadyRunning = false;
}

void SocketHandler::addSocket(string uid, Socket *socket)
{
	cout << "SocketHandler-> Adding socket \"" << uid << "\"" << endl;
	WebSocketServer::checkHandshake(1, "");
	sockets[uid] = socket;
}

void SocketHandler::removeSocket(string uid)
{
	cout << "SocketHandler-> Removing socket \"" << uid << "\"" << endl;
	Socket *del = sockets[uid];
	sockets.erase(uid);
	if(del != NULL)
	{
		delete del;
		del = NULL;
	}
}
