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

using namespace boost::asio;

class client
{
private:
    std::string host;
    std::string port;
public:
    client(std::string host, std::string port) : port(port), host(host) {

    }
    void operator()() {
        try {
            io_service aios;

            ip::tcp::resolver resolver(aios);
            ip::tcp::resolver::iterator endpoint = resolver.resolve(
                    ip::tcp::resolver::query(host, port));
            ip::tcp::socket socket(aios);
            // open the connection for the specified endpoint, or throws a system_error
            connect(socket, endpoint);
            for(;;) {
                std::array<char, 512> buf;
                boost::system::error_code error;
                size_t lenghtOfReceived = socket.read_some(buffer(buf), error);

                if (error == error::eof) {
                    break; // Connection closed cleanly by peer
                } else if(error) {
                    throw boost::system::system_error(error);
                }
                std::cout.write(buf.data(), lenghtOfReceived);
                std::cout << '|';
                std::cout.flush();
            }
            std::cout << std::endl;
        } catch(std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
};

int main(int argc, char* argv[])
{
    client client_("localhost", argv[1]);
    client_();
}
