#include <boost/thread.hpp>
#include "comparator_app.hpp"
#include "../network/client.hpp"
#include "../network/blocking_queue.hpp"

using namespace comparator_app;
using namespace network;

void start_compare(std::shared_ptr<comparator_module> comparator_module_,
        std::shared_ptr<blocking_queue> generator_queue,
        std::shared_ptr<blocking_queue> filter_queue) {
    comparator_module_->run(generator_queue, filter_queue);
}

int main(int argc, char ** argv) {
    if (argc != 5) {
        std::cout
                << "Usage: comparator_app <generator_host> <generator_port> <filter_host> <filter_port>"
                << std::endl;
    } else {
        std::shared_ptr<blocking_queue> generator_queue(new blocking_queue);
        std::shared_ptr<blocking_queue> filter_queue(new blocking_queue);

        client generator_client(argv[1], argv[2], generator_queue);
        client filter_client(argv[3], argv[4], filter_queue);
        boost::thread filter_thread(filter_client);
        boost::thread generator_thread(generator_client);
        boost::thread comparator_thread(
                boost::bind(start_compare, comparator_module::get_instance(),
                        generator_queue, filter_queue));
        generator_thread.join();
        comparator_module::get_instance()->stop(generator_queue, filter_queue);
        generator_thread.join();
        comparator_thread.join();
    }
}
