/**
 * \file client.hpp
 * \author Adam Mościcki
 */


#include <exception>
#include <array>
#include <iostream>
#include <boost/asio.hpp>

#include "blocking_queue.hpp"
#include "connection_commons.hpp"

namespace network {

/**
 * Client
 */
class client {
private:
    std::string host_;
    std::string port_;
    std::shared_ptr<blocking_queue> queue_;
public:
    /**
     * Creats a client
     * \param host host
     * \param port port
     * \param queue blocking_queue where client push received data
     */
    client(std::string host, std::string port, std::shared_ptr<blocking_queue> queue);
    /**
     * Start a client
     */
    void operator()();


};

}
