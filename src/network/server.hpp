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

class server {
private:
    int port_;
    std::shared_ptr<sending_buffer> sending_buf_;
    volatile bool is_started_;
public:
    server(int port, std::shared_ptr<sending_buffer> ptr);
    void operator()();
    void send(std::shared_ptr<boost::asio::ip::tcp::socket> socket, std::shared_ptr<sending_buffer> sending_buf);
    void stop();
};

}
