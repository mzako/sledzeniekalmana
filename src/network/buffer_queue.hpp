/**
 * \file buffer_queue.hpp
 * \author Adam Mościcki
 */

#ifndef _BUFFER_QUEUE_HPP
#define _BUFFER_QUEUE_HPP

#include <boost/thread/mutex.hpp>
#include <queue>
#include <string>

/**
 * \details Queue of strings with thread safe operations, poping operation on empty buffer blocks thread till to push.
 */
class buffer_queue
{
    private:
        boost::mutex safe;
        std::queue<std::string> messages;
        boost::mutex lock_empty;
    public:
        buffer_queue();
        std::string pop();
        void push(std::string message);
};

#endif
