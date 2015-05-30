all: server client

clean:
	rm *.o server client

server: main_server.o server.o buffer_queue.o sending_buffer.o
	g++ main_server.o buffer_queue.o sending_buffer.o -o server -lboost_system -lpthread -L/usr/local/lib/ -lboost_thread

main_server.o: main_server.cpp
	g++ main_server.cpp -o main_server.o -std=c++0x -g -c

server.o: server.cpp
	g++ server.cpp -o server.o -std=c++0x -g -c
	
sending_buffer.o: sending_buffer.cpp
	g++ sending_buffer.cpp -o sending_buffer.o -std=c++0x -g -c

buffer_queue.o: buffer_queue.cpp
	g++ buffer_queue.cpp -o buffer_queue.o -std=c++0x -c -g

client: main_client.o client.o
	g++ main_client.o client.o -o client -lboost_system -lpthread -L/user/local/lib -lboost_thread

client.o: client.cpp
	g++ client.cpp -o client.o -std=c++0x -c -g

main_client.o: main_client.cpp
	g++ main_client.cpp -o main_client.o -std=c++0x -c -g

