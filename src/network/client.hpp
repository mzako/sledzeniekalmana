/**
 * \file client.hpp
 * \author Adam Mościcki
 */

#ifndef _CLIENT_HPP
#define _CLIENT_HPP


#include <exception>
#include <array>
#include <iostream>
#include <boost/asio.hpp>

#include "blocking_queue.hpp"
#include "connection_commons.hpp"

namespace network {

/**
 * \brief TCP client
 */
class client {
public:
    /**
     * \brief Creates a client with given host, port and blocking_queue
     *
     * \param host given host
     * \param port given port
     * \param queue blocking_queue where client push received data
     */
    client(std::string host, std::string port, std::shared_ptr<blocking_queue> queue);
    /**
     * \brief Start a client
     */
    void operator()();
    /**
     * \brief Stop a client
     */
    void stop();

private:
    std::string host_;
    std::string port_;
    std::shared_ptr<blocking_queue> queue_;
    volatile bool is_started_;
};

}

#endif
