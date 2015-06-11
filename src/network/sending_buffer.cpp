/**
 * \file sending_buffer.cpp
 * \brief This file contains sending_buffer class' definitions
 * \author Adam Mościcki
 */
#include "sending_buffer.hpp"

namespace network {

void sending_buffer::addThread(boost::thread::id id) {
    safe.lock();
    buffersForThreads[id] = std::shared_ptr<blocking_queue>(new blocking_queue);
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
    std::shared_ptr<blocking_queue> threadBuffer;
    std::string result;
    safe.lock();
    threadBuffer = buffersForThreads[id];
    safe.unlock();
    return  threadBuffer->pop();
}

} /* namespace network */
