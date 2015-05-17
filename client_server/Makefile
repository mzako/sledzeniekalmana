all: server client

server: server.cpp
	g++ server.cpp -o server -std=c++0x -lboost_system -lpthread -g -L/usr/local/lib/ -lboost_thread
client: client.cpp
	g++ client.cpp -o client -std=c++0x -lboost_system -lpthread -g

