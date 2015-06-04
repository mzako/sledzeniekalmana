/**
 * \file buffer_queue.hpp
 * \author Adam Mościcki
 */

#ifndef _BLOCKING_QUEUE_HPP
#define _BLOCKING_QUEUE_HPP

#include <boost/thread/mutex.hpp>
#include <queue>
#include <string>

/**
 * \details Queue of strings with thread safe operations, poping operation on empty buffer blocks thread till to push.
 */

namespace network {

class blocking_queue {
    private:
        boost::mutex safe;
        std::queue<std::string> messages;
        boost::mutex lock_empty;
    public:
        blocking_queue();
        std::string pop();
        void push(std::string message);
};

}

#endif
