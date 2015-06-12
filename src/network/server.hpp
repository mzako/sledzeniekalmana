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
#include <boost/thread/thread.hpp>
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
 * \brief TCP server
 */
class server {
private:
    int port_;
    std::shared_ptr<sending_buffer> sending_buf_;
    std::string initial_data_;
    std::shared_ptr<boost::thread_group> thread_group_;
    volatile bool is_started_;
protected:
    void write_to_socket(std::shared_ptr<boost::asio::ip::tcp::socket> socket,
            const std::string & message);
public:
    /**
     * Creates server on given port with given sending buffer
     * \param pprt given port, on which server will listen
     * \param ptr smart pointer to sending_buffer which server will use to propagate messages
     */
    server(int port, std::shared_ptr<sending_buffer> ptr,
            std::string initial_data = "");
    /**
     * \brief Main listening loop of server, for thread usage
     */
    void operator()();
    /**
     * \brief Start working loop new connection is accepted.
     *
     * Should be started in new thread.
     * \param socket assign connection socket
     * \param sending_buf buffer which server uses for with messages to send
     */
    void send(std::shared_ptr<boost::asio::ip::tcp::socket> socket,
            std::shared_ptr<sending_buffer> sending_buf);
    /**
     * \brief Stops the server
     */
    void stop();
};

}

#endif
