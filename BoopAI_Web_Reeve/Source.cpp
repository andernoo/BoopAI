#include "websocket.h" 
#include "HTTPProcessor.h"
#include "SocketHandler.h"
#include "Source.h"
#include <winsock2.h>
#include <windows.h>
#include <iostream>

int main()
{
	HTTPServer *server = new HTTPServer();	
	SocketHandler::runLoop();
}