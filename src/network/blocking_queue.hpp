/**
 * \file buffer_queue.hpp
 * \author Adam Mościcki
 */

#ifndef _BLOCKING_QUEUE_HPP
#define _BLOCKING_QUEUE_HPP

#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>
#include <queue>
#include <string>

/**
 * \details Queue of strings with thread safe operations, poping operation on empty buffer blocks thread till to push.
 */

namespace network {

class blocking_queue {
    private:
        std::queue<std::string> messages;
        boost::mutex safe_;
        boost::condition_variable wait_;
    public:
        /**
         *
         */
        blocking_queue();
        /**
         * Pop an element from Queue, if queue is empty it blocks till someone push something into
         */
        std::string pop();
        /**
         * Add an element to Queue
         * \param message element to add
         */
        void push(std::string message);
};

}

#endif
