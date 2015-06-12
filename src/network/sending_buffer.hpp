/**
 * \file sending_buffer.hpp
 * \author Adam Mościcki
 */

#ifndef _SENDING_BUFFER_HPP
#define _SENDING_BUFFER_HPP
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/shared_ptr.hpp>
#include <map>
#include <string>

#include "blocking_queue.hpp"

namespace network {
/**
 * \brief Keeps a buffer containg messages for every thread
 *
 * \b WARNING: redundacy, same messages are kept in every buffer, but it's much easier)
 */
class sending_buffer {
public:
    /**
     * \defcon
     */
    sending_buffer() {
    }
    ;
    /**
     * \brief Add thread to buffer thread pool
     *
     * \param id thread id which will be added to pool of threads receiving messages from buffer
     */
    void addThread(boost::thread::id id);
    /**
     * \brief Send message to all threads in pool.
     *
     * \param message message to broadcast
     */
    void send(std::string message);
    /**
     * \brief Get message from buffer.
     *
     * Threads use this method to get message from a buffer,
     * when buffer is empty thread function blocks on pop operation.
     */
    std::string pop(boost::thread::id id);
private:
    std::map<boost::thread::id, std::shared_ptr<blocking_queue>> buffersForThreads;
    boost::mutex safe;
};

}
#endif

