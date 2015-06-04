#include <cstdlib>
#include <iostream>
#include <memory>
#include <boost/thread/thread.hpp>
#include "../network/client.hpp"
#include "../network/blocking_queue.hpp"
#include "filter_module.hpp"

using namespace filter_app;
using namespace network;

int main(int argc, char ** argv)
{
    if(argc != 3)
    {
        std::cout << "Usage: filter_app <host> <port>" << std::endl;
    }
    else
    {
        std::shared_ptr<blocking_queue> queue(new blocking_queue);
        client client( argv[1], argv[2], queue);

        boost::thread client_thread(client);

        filter_module::get_instance()->run() ;

        return 0;
    }
}
