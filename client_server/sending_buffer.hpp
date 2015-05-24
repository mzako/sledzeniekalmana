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
#include "buffer_queue.hpp"

/**
 * \details For every thread keeps a buffer containg messages
 * (WARNING: redundacy, same messages are kept in every buffer, it's much easier)
 *
 */
class sending_buffer
{
    std::map<boost::thread::id, boost::shared_ptr<buffer_queue>> buffersForThreads;
    boost::mutex safe;
    public:
    sending_buffer(){
    };
    
    void addThread(boost::thread::id id);

    void send(std::string message);

    /**
     * Every thread use this method to get message from a buffer, 
     * when buffer is empty thread blocks on pop operation in return line
     */
    std::string pop(boost::thread::id id);
};

#endif


