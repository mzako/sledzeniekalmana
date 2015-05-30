#include <iostream>
#include <exception>
#include <array>
#include <queue>
#include <map>
#include <string>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <memory>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "sending_buffer.hpp"
#include "buffer_queue.hpp"

using namespace boost::asio;

class server
{
private:
    int port;
    std::shared_ptr<sending_buffer> sending_buf;
public:
    server(int port, std::shared_ptr<sending_buffer> ptr);
    void operator()();
    static void send(std::shared_ptr<ip::tcp::socket> socket, std::shared_ptr<sending_buffer> sending_buf);
};
