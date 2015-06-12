#ifndef TEST

#include <cstdlib>
#include <iostream>
#include <memory>
#include <boost/thread/thread.hpp>
#include <fstream>

#include "../commons/cout_writer.hpp"
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
int main(int argc, char ** argv) {

    if (argc != 4) {
        std::cout
                << "Usage: generator_app <filter_port> <comparator_port> <init_file_path>"
                << std::endl;
    } else {
        // checing simulation file
        std::fstream file;
        file.open(argv[3], std::fstream::in);
        if (!file.is_open()) {
            std::cout << "Cannot open file: " << argv[3] << std::endl;
            return 1;
        }
        std::string initial_data =
                simulation_module::get_instance()->initialize(file);
        file.close();

        //filter server
        std::shared_ptr<sending_buffer> filter_sending_buf(new sending_buffer);
        server filter_server(std::atoi(argv[1]), filter_sending_buf,
                initial_data);

        //comparator server
        std::shared_ptr<sending_buffer> comparator_sending_buf(
                new sending_buffer);
        server comparator_server(std::atoi(argv[2]), comparator_sending_buf,
                initial_data);

        //network threads start
        boost::thread filter_server_thread(
                boost::bind(&server::operator(), &filter_server));
        boost::thread comparator_server_thread(
                boost::bind(&server::operator(), &comparator_server));
        boost::thread wait_for_stop(
                boost::bind(stop_simulation,
                        simulation_module::get_instance()));

        //simulation start
        simulation_module::get_instance()->run(filter_sending_buf,
                comparator_sending_buf);

#ifdef DEBUG
        commons::cout_writer() << "Simulation stopped.\n";
#endif
        filter_server.stop();
#ifdef DEBUG
        commons::cout_writer() << "Filter server stop.\n";
#endif
        comparator_server.stop();
#ifdef DEBUG
        commons::cout_writer() << "Comparator server stop.\n";
#endif
        //joining threads
        filter_server_thread.join();
        comparator_server_thread.join();
    }

    return 0;
}

#endif
