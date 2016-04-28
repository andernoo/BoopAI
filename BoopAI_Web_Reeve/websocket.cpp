#include <stdio.h>
#include <algorithm>
#include <string>   //strlen
#include <cstring>
#include <stdlib.h>
#include <csignal>
#include <errno.h>
#include <vector>
#ifdef _WIN32
#include <winsock2.h>
#include <Ws2tcpip.h>
#else
#include <arpa/inet.h>    //close
#include <sys/socket.h>
#include <netinet/in.h>
#endif
#include <sys/types.h>
#include <iostream>

#include <time.h> //FD_SET, FD_ISSET, FD_ZERO macros
#include "sha1.h"
#include <map>
#include "websocket.h"

using namespace std;

const string WebSocketServer::base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";;
int WebSocketServer::master_socket;
map<int, string> WebSocketServer::websocks;
bool WebSocketServer::test()
{
	return true;
}
string WebSocketServer::base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len)
{
	std::string ret;
	int i = 0;
	int j = 0;
	unsigned char char_array_3[3];
	unsigned char char_array_4[4];

	while(in_len--)
	{
		char_array_3[i++] = *(bytes_to_encode++);
		if(i == 3)
		{
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for(i = 0; (i <4); i++)
				ret += base64_chars[char_array_4[i]];
			i = 0;
		}
	}

	if(i)
	{
		for(j = i; j < 3; j++)
			char_array_3[j] = '\0';

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;

		for(j = 0; (j < i + 1); j++)
			ret += base64_chars[char_array_4[j]];

		while((i++ < 3))
			ret += '=';

	}

	return ret;

}
void WebSocketServer::removeWS(int sd)
{
	websocks.erase(sd);
}
void WebSocketServer::sendMessage(int sd, string msg)
{
	if(isWS(sd))
	{
		msg = encode(msg.c_str());
		//msg=message;
	}
	try
	{
		send(sd, msg.c_str(), strlen(msg.c_str()), 0);
	}
	catch(const exception& ex)
	{
		printf("Websockets-> Send error %s\n", ex.what());
	}
}
void WebSocketServer::sendToAll(int sd, const char message[1024])
{
	printf("Websockets-> Sending: '%s'\n", message);
	for(int i = 0; i<30; i++)
	{
		if(i != sd && i != master_socket)
		{
			sendMessage(i, message);
		}
	}
}
void WebSocketServer::addWS(int sd, string key)
{
	cout << "Websockets-> Adding " << sd << " as a websocket" << endl;
	websocks[sd] = key;
}

void WebSocketServer::setConnected(int sd)
{
	websocks[sd] = "connected";
	WebSocketServer::sendMessage(sd, "Hi!");
}

bool WebSocketServer::isWS(int sd)
{
	map<int, string>::iterator it = websocks.find(sd);
	if(it != websocks.end() && (*it).second == "connected")
	{
		return true;
	}
	return false;
}

string WebSocketServer::getKey(int sd)
{
	return websocks.at(sd);
}

bool WebSocketServer::replyHandshake(int sd, string webkey)
{
	string headers;
	unsigned char hash[20];
	webkey.append("258EAFA5-E914-47DA-95CA-C5AB0DC85B11");
	sha1::calc(webkey.c_str(), strlen(webkey.c_str()), hash);
	webkey = string(reinterpret_cast<const char*>(hash));
	webkey = base64_encode(reinterpret_cast<const unsigned char*>(webkey.c_str()), 20);

	headers = "HTTP/1.1 101 Switching Protocols\r\n";
	headers += "Upgrade: websocket\r\n";
	headers += "Connection: Upgrade\r\n";
	headers += "Sec-WebSocket-Accept: ";
	headers += webkey;
	headers += "\r\n";
	headers += "Sec-WebSocket-Protocol: boop\r\n";
	headers += "\r\n";
	int sent = 0;
	if((sent = send(sd, headers.c_str(), headers.length(), 0))>0)
	{
		printf("Websockets-> Handshake Reply Sent (%d)\n", sent);
		return true;
	}
	else
	{
		return false;
		printf("Websockets-> Reply not sent (%d)", errno);
	}
}

bool WebSocketServer::checkHandshake(int sd, string recieved)
{
	string webkeyfind = "Sec-WebSocket-Key: ";
	string::size_type found = recieved.find(webkeyfind);
	string webkey;
	if(found != string::npos)
	{
		string::size_type endline = recieved.find("\r\n", found);
		webkey = recieved.substr(found + webkeyfind.length(), 24);
		printf("Websockets-> Handshake recieved\n");
		WebSocketServer::addWS(sd, "connecting");
		return WebSocketServer::replyHandshake(sd, webkey);
	}
	return false;
}

string WebSocketServer::encode(const char* message)
{
	if(strlen(message) == 0)
	{
		return "";
	}
	char encoded[1024];
	encoded[0] = 129;
	int indexStartRawData = -1;
	if(strlen(message) <= 125)
	{
		encoded[1] = strlen(message);

		indexStartRawData = 2;
	}
	else if(strlen(message) >= 126 && strlen(message) <= 65535)
	{
		encoded[1] = 126;
		encoded[2] = (strlen(message) >> 8) & 255;
		encoded[3] = (strlen(message)) & 255;

		indexStartRawData = 4;

	}
	else
	{
		encoded[1] = 127;
		encoded[2] = (strlen(message) >> 56) & 255;
		encoded[3] = (strlen(message) >> 48) & 255;
		encoded[4] = (strlen(message) >> 40) & 255;
		encoded[5] = (strlen(message) >> 32) & 255;
		encoded[6] = (strlen(message) >> 24) & 255;
		encoded[7] = (strlen(message) >> 16) & 255;
		encoded[8] = (strlen(message) >> 8) & 255;
		encoded[9] = (strlen(message)) & 255;

		indexStartRawData = 10;
	}
	strcpy(encoded + indexStartRawData, message);

	string send = encoded;

	return send;
}

string WebSocketServer::decode(const char* buffer)
{
	char secondByte = buffer[1]; //modify the actual buffer, there's no use for the encoded data
	int length = secondByte & 127; // may not be the actual length in the two special cases
	int indexFirstMask = 2;          // if not a special case
	if(length == 126)
	{
		indexFirstMask = 4;
	}
	else if(length == 127)
	{
		indexFirstMask = 10;
	}

	char masks[4];
	strncpy(masks, buffer + indexFirstMask, 4); // four bytes starting from indexFirstMask
	int indexFirstDataByte = indexFirstMask + 4; // four bytes further
	char decoded[1024];
	unsigned int i, j;
	for(i = indexFirstDataByte, j = 0; i < strlen(buffer); i++, j++)
	{
		decoded[j] = buffer[i] ^ masks[j % 4];
	}
	decoded[j] = '\0';
	string message = decoded;
	return message;
}