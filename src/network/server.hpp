/**
 * \file server.hpp
 * \author Adam Mościcki
 */


#ifndef _SERVER_HPP
#define _SERVER_HPP

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

#include "blocking_queue.hpp"
#include "sending_buffer.hpp"
#include "connection_commons.hpp"

namespace network {
/**
 * Server
 */
class server {
private:
    int port_;
    std::shared_ptr<sending_buffer> sending_buf_;
    std::string initial_data_;
    volatile bool is_started_;
public:
    /**
     * Constructor
     * \param port port
     * \param ptr sending_buffer
     */
    server(int port, std::shared_ptr<sending_buffer> ptr, std::string initial_data = "");
    /**
     * Main thread of server
     */
    void operator()();
    /**
     * Thread method, starting when new connection was accepted
     * \param socket assing connection socket
     * \param sending_buf buffer with messages to send
     */
    void send(std::shared_ptr<boost::asio::ip::tcp::socket> socket, std::shared_ptr<sending_buffer> sending_buf);
    /**
     * Stops the serwer
     */
    void stop();
};

}

#endif
