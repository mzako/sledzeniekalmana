#include <boost/thread/thread.hpp>
#include <iostream>
#include <memory>

#include "../network/blocking_queue.hpp"
#include "../network/client.hpp"
#include "filter_module.hpp"

using namespace filter_app;
using namespace network;

int main(int argc, char ** argv){

    if(argc != 3)
    {
        std::cout << "Usage: filter_app <host> <port>" << std::endl;
    }
    else
    {
        std::shared_ptr<blocking_queue> buf_queue(new blocking_queue);
        client filter_client(argv[1], argv[2], buf_queue);
        boost::thread client_thread(filter_client);

        filter_module::get_instance()->run(buf_queue);

    }


    return 0;
}
