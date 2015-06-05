#include <boost/thread/thread.hpp>
#include <iostream>
#include <memory>

#include "../network/blocking_queue.hpp"
#include "../network/client.hpp"
#include "filter_module.hpp"

using namespace filter_app;
using namespace network;

void start_filter(std::shared_ptr<filter_module> filter_module_, std::shared_ptr<blocking_queue> queue) {
    filter_module_->run(queue);
}

int main(int argc, char ** argv){

    if(argc != 3)
    {
        std::cout << "Usage: filter_app <host> <port>" << std::endl;
    }
    else
    {
        std::shared_ptr<blocking_queue> queue(new blocking_queue);
        client filter_client(argv[1], argv[2], queue);
        boost::thread client_thread(filter_client);
        boost::thread filter_thread(boost::bind(start_filter, filter_module::get_instance(), queue));
        client_thread.join();
        filter_module::get_instance()->stop(queue); //ugly solution
        filter_thread.join();
    }


    return 0;
}
