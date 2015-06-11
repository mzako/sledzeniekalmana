/**
 * \file blocking_queue.cpp
 * \brief This file contains blocking_queue class' functions definitions
 * \author Adam Mościcki
 */

#include "blocking_queue.hpp"

using namespace network;

blocking_queue::blocking_queue() {
}

std::string blocking_queue::pop() {
    boost::mutex::scoped_lock s_safe(safe_);
    while(messages.empty()) {
        wait_.wait(s_safe);
    }
    std::string result;
    result = messages.front();
    messages.pop();
    return result;

}

void blocking_queue::push(std::string message) {
    boost::mutex::scoped_lock s_safe(safe_);
    messages.push(message);
    s_safe.unlock();
    wait_.notify_all();
}
