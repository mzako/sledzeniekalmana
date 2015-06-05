#include "../src/network/client.hpp"
#include "../src/network/blocking_queue.hpp"
#include <boost/thread.hpp>

using namespace network;

//przykladowy watek nadawczy
void receiving_thread(std::shared_ptr<blocking_queue> queue)
{
    try
    {
        while(true)
        {
            std::cout << queue->pop() << std::endl;
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception in thread:" << e.what() << "\n";
    }
}

int main(int argc, char* argv[])
{
    std::shared_ptr<blocking_queue> queue(new blocking_queue);
    client client_("localhost", argv[1], queue);
    boost::thread rct(boost::bind(receiving_thread, queue));
    client_();
}
