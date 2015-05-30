/**
 * tcpIpCs.cpp
 *
 * http://thisthread.blogspot.com/2011/02/minimal-asio-tcp-server.html
 * http://thisthread.blogspot.com/2011/02/minimal-asio-tcp-client.html
 *
 * http://www.boost.org/doc/libs/1_54_0/doc/html/boost_asio/tutorial/tutdaytime1.html
 * http://www.boost.org/doc/libs/1_54_0/doc/html/boost_asio/tutorial/tutdaytime2.html
 *
 */

#include <iostream>
#include <exception>
#include <array>
#include <queue>
#include <map>
#include <string>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "sending_buffer.hpp"
#include "buffer_queue.hpp"

using namespace boost::asio;

boost::mutex cout_mutex;

template<typename T> void safePrint(const T &arg)
{
  cout_mutex.lock();
  std::cout << arg << std::endl;
  cout_mutex.unlock();
}


void send(boost::shared_ptr<ip::tcp::socket> socket, boost::shared_ptr<sending_buffer> sending_buf)
{
  boost::thread::id current_thread = boost::this_thread::get_id();  
  sending_buf->addThread(current_thread);
  safePrint(current_thread);
  try
  {
    while(true)
    {
      std::string message = sending_buf->pop(current_thread);
      safePrint(message);
      boost::asio::write(*socket, buffer(message));
    }
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception in thread: " << e.what() << "\n";
  }
}

//przykladowy watek nadawczy
void sending_thread(boost::shared_ptr<sending_buffer> sending_buf)
{
    try
    {
        int i = 0;
        std::string message = "aaaa";
        while(true)
        {
            boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
            std::string toSend = message + boost::lexical_cast<std::string>(i++);
            sending_buf->send(toSend);
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception in thread:" << e.what() << "\n";
    }
}

void asioTcpServer(const char * port)
{
  boost::shared_ptr<sending_buffer> sending_buf(new sending_buffer);
  boost::thread st(boost::bind(sending_thread, sending_buf));
  try
  {
    io_service service;
	io_service::work work(service);
    ip::tcp::acceptor acceptor(service,	ip::tcp::endpoint(ip::tcp::v4(), std::stoi(port)));
    // just once
    while(true) {
      boost::shared_ptr<ip::tcp::socket> socket(new ip::tcp::socket(service));
      safePrint("Server ready");
      acceptor.accept(*socket); //wait for connection
      boost::thread t(boost::bind(send, socket, sending_buf));
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
