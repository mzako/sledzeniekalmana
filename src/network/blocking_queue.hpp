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

namespace network {
/**
 * \brief Synchronised blocking queue of string.
 *
 * Queue of strings with thread safe operations, poping operation on empty buffer blocks thread till to push.
 */
class blocking_queue {
private:
    std::queue<std::string> messages;
    boost::mutex safe_;
    boost::condition_variable wait_;
public:
    /**
     * \defcon
     */
    blocking_queue();
    /**
     * \brief Pop an element from Queue.
     *
     * If queue is empty function blocks till someone push something into it.
     * \return std::string value in queue
     */
    std::string pop();
    /**
     * \brief Add an element to Queue.
     *
     * \param message element to add
     */
    void push(std::string message);
};

}

#endif
