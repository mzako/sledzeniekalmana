#include <cstdlib>
#include <iostream>
#include <memory>
#include <boost/thread/thread.hpp>
#include "../network/server.hpp"
#include "../network/sending_buffer.hpp"
#include "simulation_module.hpp"

using namespace generator_app;
using namespace network;

int main(int argc, char ** argv){

    if(argc != 4)
    {
        std::cout << "Usage: generator_app <filter_port> <comparator_port> <init_file_path>" << std::endl;
    }
    else
    {
        std::string initial_data = simulation_module::get_instance()->initialize(argv[3]);

        std::shared_ptr<sending_buffer> filter_sending_buf(new sending_buffer);
        server filter_server(std::atoi(argv[1]), filter_sending_buf, initial_data);
        std::shared_ptr<sending_buffer> comparator_sending_buf(new sending_buffer);
        server comparator_server(std::atoi(argv[2]), comparator_sending_buf);

        boost::thread filter_server_thread(filter_server);
        boost::thread comparator_server_thread(comparator_server);

        simulation_module::get_instance()->run(filter_sending_buf, comparator_sending_buf);
    }


    return 0;
}
