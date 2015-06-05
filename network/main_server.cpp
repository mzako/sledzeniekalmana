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
#include "../src/network/server.hpp"
#include "../src/network/sending_buffer.hpp"
#include "../src/network/blocking_queue.hpp"

using namespace network;

//przykladowy watek nadawczy
void sending_thread(std::shared_ptr<sending_buffer> sending_buf)
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



int main(int argc, char* argv[])
{
    if(argc >= 2) {
        std::shared_ptr<sending_buffer> sending_buf(new sending_buffer());
        boost::thread st(boost::bind(sending_thread, sending_buf));
        server server_(std::atoi(argv[1]), sending_buf);
        server_();
    } else {
        std::cout << "Spec port";
    }
}
