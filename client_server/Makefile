all: server client

server: server.o buffer_queue.o sending_buffer.o
	g++ server.o buffer_queue.o sending_buffer.o -o server -lboost_system -lpthread -L/usr/local/lib/ -lboost_thread

server.o: server.cpp
	g++ server.cpp -o server.o -std=c++0x -g -c
	
sending_buffer.o: sending_buffer.cpp
	g++ sending_buffer.cpp -o sending_buffer.o -std=c++0x -g -c


buffer_queue.o: buffer_queue.cpp
	g++ buffer_queue.cpp -o buffer_queue.o -std=c++0x -c -g



client: client.cpp
	g++ client.cpp -o client -std=c++0x -lboost_system -lpthread -g

