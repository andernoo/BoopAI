cmake_minimum_required (VERSION 2.6)
project (BoopAI)

# configure a header file to pass some of the CMake settings
# to the source code

# add the executable
add_executable(booopai-server NeuralNetwork.cpp Boop.cpp BoopPlanet.cpp BoopUniverse.cpp Main.cpp)

#CFLAGS = -g -std=c++11 -pthread -lboost_system -lboost_regex -lcrypto -lssl -lBox2D

#$(CC) $(CFLAGS) MathUtilities.cpp NeuralNetwork.cpp Boop.cpp BoopPlanet.cpp BoopUniverse.cpp Main.cpp -o boopai-server
