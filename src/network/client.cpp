/**
 * tcpIpCs.cpp
 *
 * http://thisthread.blogspot.com/2011/02/minimal-asio-tcp-server.html
 * http://thisthread.blogspot.com/2011/02/minimal-asio-tcp-client.html
 *
 * http://www.boost.org/doc/libs/1_54_0/doc/html/boost_asio/tutorial/tutdaytime1.html
 * http://www.boost.org/doc/libs/1_54_0/doc/html/boost_asio/tutorial/tutdaytime2.html
 */

#include "client.hpp"

using namespace boost::asio;
using namespace network;

client::client(std::string host, std::string port, std::shared_ptr<blocking_queue> queue)
                                                : port_(port), host_(host), queue_(queue) {

}

void client::operator()() {
    try {
        io_service aios;

        ip::tcp::resolver resolver(aios);
        ip::tcp::resolver::iterator endpoint = resolver.resolve(
                ip::tcp::resolver::query(host_, port_));
        ip::tcp::socket socket(aios);
        // open the connection for the specified endpoint, or throws a system_error
        connect(socket, endpoint);
        std::string message;
        for(;;) {
            while(true) {
                std::array<char, 512> buf;
                boost::system::error_code error;
                size_t lenghtOfReceived = socket.read_some(buffer(buf), error);
                if (error == error::eof) {
                    break; // Connection closed cleanly by peer
                } else if(error) {
                    throw boost::system::system_error(error);
                }
                std::string result = std::string(buf.data()).substr(0, lenghtOfReceived);
                size_t position = result.find(connection_commons::END_OF_MESSAGE);
                if (position != std::string::npos) {
                    message += result.substr(0, position); //doddajemy koncowke
                    queue_->push(message);
                    message.clear();
                    message += result.substr(position + connection_commons::END_OF_MESSAGE.size(), result.size()); //nowy message bez poczatku
                    break;
                } else {
                    message += result;
                }
            }
        }
    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}