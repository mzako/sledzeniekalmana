#include "server.hpp"


using namespace boost::asio;


server::server(int port, std::shared_ptr<sending_buffer> ptr)
        : port(port), sending_buf(ptr) {
}


void server::send(std::shared_ptr<ip::tcp::socket> socket, std::shared_ptr<sending_buffer> sending_buf)
{
    boost::thread::id current_thread = boost::this_thread::get_id();
    sending_buf->addThread(current_thread);
    try
    {
        while(true)
        {
            std::string message = sending_buf->pop(current_thread);
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
            std::shared_ptr<ip::tcp::socket> socket(new ip::tcp::socket(service));
            acceptor.accept(*socket); //wait for connection
            auto run = boost::bind(server::send, socket, sending_buf);
            boost::thread t(run);
        }
    } catch(std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

