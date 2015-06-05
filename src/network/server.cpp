#include "server.hpp"

using namespace boost::asio;
using namespace network;

server::server(int port, std::shared_ptr<sending_buffer> ptr, std::string initial_data)
        : port_(port), initial_data_(initial_data), sending_buf_(ptr), thread_group_(new boost::thread_group), is_started_(true) {
}


void server::send(std::shared_ptr<ip::tcp::socket> socket, std::shared_ptr<sending_buffer> sending_buf)
{
    boost::thread::id current_thread = boost::this_thread::get_id();
    sending_buf->addThread(current_thread);
    try
    {
        write(*socket, buffer(initial_data_));
        while(is_started_)
        {
            std::string message = sending_buf->pop(current_thread);
            message += connection_commons::END_OF_MESSAGE;
            write(*socket, buffer(message));
        }
        write(*socket, buffer(connection_commons::CLOSE_CONNECTION + connection_commons::END_OF_MESSAGE));
        socket->close();
        std::cout << "Closing connection" << std::endl;
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
        ip::tcp::acceptor acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), port_));
        // just once
        int i = 0;
        while(is_started_) {
            if(++i > 2) {
                stop();
            }
            std::shared_ptr<ip::tcp::socket> socket(new ip::tcp::socket(service));
            acceptor.accept(*socket); //wait for connection q

            boost::function<void (std::shared_ptr<ip::tcp::socket> , std::shared_ptr<sending_buffer>)> run(boost::bind(&server::send, this, _1, _2));
            thread_group_->create_thread(boost::bind(run, socket, sending_buf_));
        }
        thread_group_->join_all();
    } catch(std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

void server::stop() {
    is_started_ = false; //there is no need to safe this var
    io_service aios;
    ip::tcp::resolver resolver(aios);
    ip::tcp::resolver::iterator endpoint = resolver.resolve(
            ip::tcp::resolver::query("localhost", std::to_string(port_)));
    ip::tcp::socket socket(aios);
    // open the connection for the specified endpoint, or throws a system_error
    connect(socket, endpoint);
}
