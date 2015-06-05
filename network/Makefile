all: server client

clean:
	rm *.o server client

server: main_server.o 
	g++ main_server.o -o server -lboost_system -lpthread -L/usr/local/lib/ -lboost_thread -L../build/debug/network -lnetwork

main_server.o: main_server.cpp
	g++ main_server.cpp -o main_server.o -std=c++0x -g -c

client: main_client.o 
	g++ main_client.o -o client -lboost_system -lpthread -L/user/local/lib -lboost_thread -L../build/debug/network -lnetwork

main_client.o: main_client.cpp
	g++ main_client.cpp -o main_client.o -std=c++0x -c -g

