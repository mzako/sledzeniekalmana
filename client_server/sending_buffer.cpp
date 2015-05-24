#include "sending_buffer.hpp"

void sending_buffer::addThread(boost::thread::id id) {
    safe.lock();
    buffersForThreads[id] = boost::shared_ptr<buffer_queue>(new buffer_queue);
    safe.unlock();
}

void sending_buffer::send(std::string message) {
    safe.lock();
    for (auto it = buffersForThreads.begin(); it != buffersForThreads.end(); it++) {
        it->second->push(message);
    }
    safe.unlock();
}

/**
 * Every thread use this method to get message from a buffer, 
 * when buffer is empty thread blocks on pop operation in return line
 */
std::string sending_buffer::pop(boost::thread::id id) {
    boost::shared_ptr<buffer_queue> threadBuffer;
    std::string result;
    safe.lock();
    threadBuffer = buffersForThreads[id];
    safe.unlock();
    return  threadBuffer->pop();
}

