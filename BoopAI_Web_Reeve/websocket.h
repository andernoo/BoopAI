#include <map>
#ifndef WEBSOCKETS
#define WEBSOCKETS

using namespace std;
class WebSocketServer
{
private:
	static int master_socket;
public:
	static bool test();
	static map<int, string> websocks;
	static const string base64_chars;
	static string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len);
	static void removeWS(int sd);
	static void sendMessage(int sd, string msg);
	static void sendToAll(int sd, const char message[1024]);
	static void addWS(int sd, string key);
	static void setConnected(int sd);
	static bool isWS(int sd);
	static string getKey(int sd);

	static bool replyHandshake(int sd, string webkey);

	static bool checkHandshake(int sd, string recieved);

	static string encode(const char* message);

	static string decode(const char* buffer);
};
#endif // WEBSOCKETS