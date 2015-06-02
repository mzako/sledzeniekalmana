#include "simulation_module.hpp"
#include <memory>
#include "../network/server.hpp"
#include "../network/sending_buffer.hpp"
using namespace generator_app;
using namespace network;
int main(int argc, char ** argv){

    std::shared_ptr<sending_buffer> sending_buf(new sending_buffer);
    server server_(std::atoi(argv[1]), sending_buf);
    simulation_module * instance = simulation_module::get_instance();
    boost::thread server_thread(server_);
    instance->run(sending_buf);

    return 0;
}
