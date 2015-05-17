/**
 * tcpIpCs.cpp
 *
 * http://thisthread.blogspot.com/2011/02/minimal-asio-tcp-server.html
 * http://thisthread.blogspot.com/2011/02/minimal-asio-tcp-client.html
 *
 * http://www.boost.org/doc/libs/1_54_0/doc/html/boost_asio/tutorial/tutdaytime1.html
 * http://www.boost.org/doc/libs/1_54_0/doc/html/boost_asio/tutorial/tutdaytime2.html
 */

#include <iostream>
#include <exception>
#include <array>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>

using namespace boost::asio;

boost::mutex cout_mutex;

template<typename T> void safePrint(const T &arg)
{
  cout_mutex.lock();
   std::cout << arg << std::endl;
  cout_mutex.unlock();
}


void send(boost::shared_ptr<ip::tcp::socket> socket)
{
  try
  {
    while(true)
    {
	  sleep(1);
      safePrint("sending message");
      std::string message("Hello from ASIO");
      boost::asio::write(*socket, buffer(message));
    }
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception in thread: " << e.what() << "\n";
  }
}


void asioTcpServer(const char * port)
{
  try
  {
    io_service service;
	io_service::work work(service);
    ip::tcp::acceptor acceptor(service,	ip::tcp::endpoint(ip::tcp::v4(), std::stoi(port)));
    // just once
    while(true) {
      boost::shared_ptr<ip::tcp::socket> socket(new ip::tcp::socket(service));
      std::cout << "Server ready" << std::endl;
      acceptor.accept(*socket); //wait for connection
      boost::thread t(boost::bind(send, socket));
    }
  }
  catch(std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << std::endl;
  }
}

int main(int argc, char* argv[])
{
  if(argc >= 2) {
    asioTcpServer(argv[1]);
  } else {
    std::cout << "Spec port";
  }
}
