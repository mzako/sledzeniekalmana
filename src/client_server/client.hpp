#include <exception>
#include <array>
#include <boost/asio.hpp>

using namespace boost::asio;

class client
{
private:
    std::string host_;
    std::string port_;
public:
    client(std::string host, std::string port);
    void operator()();
};
