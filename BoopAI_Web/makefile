CC = g++ -m64
CFLAGS = -g -std=c++11 -pthread -lboost_system -lboost_regex -lcrypto -lssl
INCLUDES = -I/home/andrew/BoopAI/Box2D/

all: Main.cpp
	$(CC) $(CFLAGS) $(INCLUDES) MathUtilities.cpp NeuralNetwork.cpp Boop.cpp BoopPlanet.cpp BoopUniverse.cpp Main.cpp -o boopai-server

clean:
	rm *o boopai-server
