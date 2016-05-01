#include "server_ws.hpp"
#include <memory>
#include "BoopUniverse.h"
#include "json.hpp"
#include "MathUtilities.h"
#include "Main.h"

extern "C" { FILE __iob_func[3] = { *stdin,*stdout,*stderr }; }

using namespace std;
using json = nlohmann::json;

typedef SimpleWeb::SocketServer<SimpleWeb::WS> WssServer;

int main()
{
	srand(time(NULL));
	//WebSocket Secure (WSS)-server at port 8080 using 4 threads
	//WssServer server(2213, 4, "anooserve.com.crt", "anooserve.com.key");
	WssServer server(2213, 4);
	auto& echo = server.endpoint["^/boop/?$"];

	echo.onmessage = [&server](shared_ptr<WssServer::Connection> connection, shared_ptr<WssServer::Message> message)
	{
		/*//WssServer::Message::string() is a convenience function for:
		//stringstream data_ss;
		//data_ss << message->rdbuf();
		//auto message_str = data_ss.str();
		auto message_str = message->string();

		cout << "Server: Message received: \"" << message_str << "\" from " << (size_t)connection.get() << endl;

		cout << "Server: Sending message \"" << message_str << "\" to " << (size_t)connection.get() << endl;

		auto send_stream = make_shared<WssServer::SendStream>();
		*send_stream << message_str;
		//server.send is an asynchronous function
		server.send(connection, send_stream, [](const boost::system::error_code& ec)
		{
			if(ec)
			{
				cout << "Server: Error sending message. " <<
					//See http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/reference.html, Error Codes for error code meanings
					"Error: " << ec << ", error message: " << ec.message() << endl;
			}
		});*/
	};

	echo.onopen = [](shared_ptr<WssServer::Connection> connection)
	{
		cout << "Server: Opened connection " << (size_t)connection.get() << endl;
	};

	//See RFC 6455 7.4.1. for status codes
	echo.onclose = [](shared_ptr<WssServer::Connection> connection, int status, const string& reason)
	{
		cout << "Server: Closed connection " << (size_t)connection.get() << " with status code " << status << endl;
	};

	//See http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/reference.html, Error Codes for error code meanings
	echo.onerror = [](shared_ptr<WssServer::Connection> connection, const boost::system::error_code& ec)
	{
		cout << "Server: Error in connection " << (size_t)connection.get() << ". " <<
			"Error: " << ec << ", error message: " << ec.message() << endl;
	};

	thread server_thread([&server]()
	{
		//Start WSS-server
		server.start();
	});

	BoopUniverse* universe = new BoopUniverse();
	universe->addPlanet(4);
	float angle = 0;
	std::chrono::milliseconds deltaTime;
	std::chrono::high_resolution_clock::time_point lastRun = std::chrono::high_resolution_clock::now();
	while(1)
	{
		universe->step();

		deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock().now() - lastRun);
		if(deltaTime.count() > 17)
		{
			json j;
			j["count"] = server.get_connections().size();
			std::vector<Boop*> boops = universe->getPlanet(0)->getBoops();
			for(auto i = boops.begin(); i != boops.end(); i++)
			{
				Boop* boop = (*i);
				j["boops"][boop->id]["id"] = boop->id;
				j["boops"][boop->id]["x"] = boop->body->GetPosition().x;
				j["boops"][boop->id]["y"] = boop->body->GetPosition().y;
				j["boops"][boop->id]["angle"] = boop->body->GetAngle();
				j["boops"][boop->id]["r"] = boop->colour.x;
				j["boops"][boop->id]["g"] = boop->colour.y;
				j["boops"][boop->id]["b"] = boop->colour.z;

			}

			for(auto a_connection : server.get_connections())
			{
				auto send_stream = std::make_shared<WssServer::SendStream>();
				*send_stream << j.dump();
				server.send(a_connection, send_stream);
			}
			lastRun = std::chrono::high_resolution_clock().now();
		}
	}

	server_thread.join();
	return 0;
}
