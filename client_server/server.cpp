#include "server.hpp"


using namespace boost::asio;

boost::mutex cout_mutex;

template<typename T> void safePrint(const T &arg)
{
    cout_mutex.lock();
    std::cout << arg << std::endl;
    cout_mutex.unlock();
}

server::server(int port, boost::shared_ptr<sending_buffer> ptr)
        : port(port), sending_buf(ptr) {
}


void server::send(boost::shared_ptr<ip::tcp::socket> socket, boost::shared_ptr<sending_buffer> sending_buf)
{
    boost::thread::id current_thread = boost::this_thread::get_id();
    sending_buf->addThread(current_thread);
    safePrint(current_thread);
    try
    {
        while(true)
        {
            std::string message = sending_buf->pop(current_thread);
            safePrint(message);
            boost::asio::write(*socket, buffer(message));
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception in thread: " << e.what() << "\n";
    }
}


void server::operator()() {
    try {
        io_service service;
        io_service::work work(service);
        ip::tcp::acceptor acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), port));
        // just once
        while(true) {
            boost::shared_ptr<ip::tcp::socket> socket(new ip::tcp::socket(service));
            safePrint("Server ready");
            acceptor.accept(*socket); //wait for connection
            auto run = boost::bind(server::send, socket, sending_buf);
            boost::thread t(run);
        }
    } catch(std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

