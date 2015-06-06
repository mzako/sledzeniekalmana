#include <iostream>
#include <memory>
#include <boost/thread/thread.hpp>

#include "filter_app.hpp"
#include "../network/blocking_queue.hpp"
#include "../network/client.hpp"
#include "../network/sending_buffer.hpp"
#include "../network/server.hpp"

using namespace filter_app;
using namespace network;

void start_filter(std::shared_ptr<filter_module> filter_module_, std::shared_ptr<blocking_queue> b_queue, std::shared_ptr<sending_buffer> sending_buffer) {
    filter_module_->run(b_queue, sending_buffer);
}

int main(int argc, char ** argv){

    if(argc != 4)
    {
        std::cout << "Usage: filter_app <gen_host> <gen_port> <filt_server_port>" << std::endl;
    }
    else
    {
        std::shared_ptr<sending_buffer> filter_sending_buf(new sending_buffer);
        server filter_server(std::atoi(argv[3]), filter_sending_buf);
        boost::thread filter_server_thread(boost::bind(&server::operator(), &filter_server));

        std::shared_ptr<blocking_queue> b_queue(new blocking_queue);
        client filter_client(argv[1], argv[2], b_queue);
        boost::thread client_thread(filter_client);

        boost::thread filter_main_thread(boost::bind(start_filter, filter_module::get_instance(), b_queue, filter_sending_buf));
        client_thread.join();
        filter_module::get_instance()->stop(b_queue);
        filter_server.stop();
        filter_server_thread.join();
        filter_main_thread.join();

    }


    return 0;
}
