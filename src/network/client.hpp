#include <exception>
#include <array>
#include <iostream>
#include <boost/asio.hpp>

#include "blocking_queue.hpp"
#include "connection_commons.hpp"

namespace network {

class client {
private:
    std::string host_;
    std::string port_;
    std::shared_ptr<blocking_queue> queue_;
public:
    client(std::string host, std::string port, std::shared_ptr<blocking_queue> queue);
    void operator()();


};

}
