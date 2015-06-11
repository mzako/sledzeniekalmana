/**
 * \file server.cpp
 * \brief This file contains client class' definitions
 * \author Adam Mościcki
 */
#include "server.hpp"

using namespace boost::asio;
namespace network {

server::server(int port, std::shared_ptr<sending_buffer> ptr, std::string initial_data)
        : port_(port), initial_data_(initial_data), sending_buf_(ptr), thread_group_(new boost::thread_group), is_started_(true) {
}


void server::send(std::shared_ptr<ip::tcp::socket> socket, std::shared_ptr<sending_buffer> sending_buf)
{
    std::cout << "Sending thread" << (unsigned int *) this << "is_started_" << is_started_ <<  std::endl;
    boost::thread::id current_thread = boost::this_thread::get_id();
    sending_buf->addThread(current_thread);
    try {

        write_to_socket(socket, initial_data_);
        while (true) {
            std::string message = sending_buf->pop(current_thread);
            if(is_started_) { //jesli wystartowana to pusc dalej
                write_to_socket(socket, message);
            } else {
                break;
            }
        }
        write_to_socket(socket, connection_commons::CLOSE_CONNECTION);
        socket->close();
        std::cout << "Closing connection" << std::endl;
    } catch (std::exception& e) {
        std::cerr << "Exception in thread: " << e.what() << "\n";
    }
}

void server::write_to_socket(std::shared_ptr<boost::asio::ip::tcp::socket> socket, const std::string & message)
{
    write(*socket, buffer(message + connection_commons::END_OF_MESSAGE));
}


void server::operator()() {
    try {
        io_service service;
        io_service::work work(service);
        ip::tcp::acceptor acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), port_));
        // just once
        bool temp_is_started;
        while(is_started_) {
            std::shared_ptr<ip::tcp::socket> socket(new ip::tcp::socket(service));
            acceptor.accept(*socket); //wait for connection q
            if(is_started_) {
                boost::function<void (std::shared_ptr<ip::tcp::socket>,
                              std::shared_ptr<sending_buffer>)> run(boost::bind(&server::send, this, _1, _2));
                thread_group_->create_thread(boost::bind(run, socket, sending_buf_));
            }
        }
        thread_group_->join_all();
    } catch(std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

void server::stop() {
    is_started_ = false; //there is no need to safe this variable, it cannot be set as true
    sending_buf_->send("");//acceptors threads can also block on pop operation, to prevent this, send empty data
    std::cout << "Stop" << (unsigned int *) this << "is_started_" << is_started_ <<  std::endl;
    //workaround to unblock accept try to connect itself
    io_service aios;
    ip::tcp::resolver resolver(aios);
    ip::tcp::resolver::iterator endpoint = resolver.resolve(
            ip::tcp::resolver::query("localhost", std::to_string(port_)));
    ip::tcp::socket socket(aios);
    // open the connection for the specified endpoint, or throws a system_error
    connect(socket, endpoint);
    socket.close();
}

} /* namespace network */
