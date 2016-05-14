cmake_minimum_required (VERSION 2.6)
project (boopai)

#Sends the -std=c++11 flag to the gcc compiler
ADD_DEFINITIONS(-std=c++11)

# add the executable
add_executable(boopai-server MathUtilities.cpp NeuralNetwork.cpp Boop.cpp BoopPlanet.cpp BoopUniverse.cpp Main.cpp)

target_link_libraries(boopai pthread boost_system boost_regex crypto ssl Box2D)

#CFLAGS = -g -std=c++11 -pthread -lboost_system -lboost_regex -lcrypto -lssl -lBox2D

#$(CC) $(CFLAGS) MathUtilities.cpp NeuralNetwork.cpp Boop.cpp BoopPlanet.cpp BoopUniverse.cpp Main.cpp -o boopai-server
