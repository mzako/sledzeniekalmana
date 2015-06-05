#include <cstdlib>
#include <iostream>
#include <memory>
#include <boost/thread/thread.hpp>
#include <fstream>

#include "../network/server.hpp"
#include "../network/sending_buffer.hpp"

#include "simulation_module.hpp"

using namespace generator_app;
using namespace network;

void stop_simulation(std::shared_ptr<simulation_module> sm) {
    std::cout << "press enter to end the simulation" << std::endl;
    std::cin.get();
    sm->stop();
}

int main(int argc, char ** argv){

    if(argc != 4)
    {
        std::cout << "Usage: generator_app <filter_port> <comparator_port> <init_file_path>" << std::endl;
    }
    else
    {
        std::fstream file;
        file.open(argv[3], std::fstream::in);
        if(!file.is_open())
        {
            std::cout << "Cannot open file: " << argv[3] << std::endl;
            return 1;
        }
        std::string initial_data = simulation_module::get_instance()->initialize(file);
        file.close();
        std::shared_ptr<sending_buffer> filter_sending_buf(new sending_buffer);
        server filter_server(std::atoi(argv[1]), filter_sending_buf, initial_data);
        std::shared_ptr<sending_buffer> comparator_sending_buf(new sending_buffer);
        server comparator_server(std::atoi(argv[2]), comparator_sending_buf);
        boost::thread filter_server_thread(boost::bind(&server::operator(), &filter_server));
        boost::thread comparator_server_thread(boost::bind(&server::operator(), &comparator_server));
        boost::thread wait_for_stop(boost::bind(stop_simulation, simulation_module::get_instance()));
        simulation_module::get_instance()->run(filter_sending_buf, comparator_sending_buf);
        std::cout << "asd";
        filter_server.stop();
        std::cout << "asd2";
        comparator_server.stop();
        std::cout << "asd3";
        filter_server_thread.join();
        comparator_server_thread.join();
    }

    return 0;
}
