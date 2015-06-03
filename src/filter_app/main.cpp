#include <cstdlib>
#include <iostream>
#include <memory>

#include <boost/thread/thread.hpp>

#include "../client_server/client.hpp"
#include "filter_module.hpp"

using namespace filter_app;

int main(int argc, char ** argv)
{
    if(argc != 3)
    {
        std::cout << "Usage: filter_app <host> <port>" << std::endl;
    }
    else
    {
        client client( argv[1], argv[2] );

        boost::thread client_thread(client);

        filter_module::get_instance()->run();

        return 0;
    }
}
