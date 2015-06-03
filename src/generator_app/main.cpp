#include <cstdlib>
#include <iostream>
#include <memory>

#include <boost/thread/thread.hpp>

#include "../client_server/sending_buffer.hpp"
#include "../client_server/server.hpp"
#include "simulation_module.hpp"

using namespace generator_app;
int main(int argc, char ** argv){

    if(argc != 3)
    {
        std::cout << "Usage: generator_app <filter_port> <comparator_port>" << std::endl;
    }
    else
    {
        std::shared_ptr<sending_buffer> filter_sending_buf(new sending_buffer);
        server filter_server(std::atoi(argv[1]), filter_sending_buf);
        std::shared_ptr<sending_buffer> comparator_sending_buf(new sending_buffer);
        server comparator_server(std::atoi(argv[2]), comparator_sending_buf);

        boost::thread filter_server_thread(filter_server);
        boost::thread comparator_server_thread(comparator_server);

        simulation_module * instance = simulation_module::get_instance();
        instance->run(filter_sending_buf, comparator_sending_buf);
    }


    return 0;
}
