/*
 * cout_writer.hpp
 *
 *  Created on: 6 Jun 2015
 *      Author: Jan Kumor
 */

#ifndef _COUT_WRITER_HPP
#define _COUT_WRITER_HPP

#include <iostream>
#include <mutex>
#include <string>

namespace commons {

class cout_writer {
public:
    cout_writer();
    virtual ~cout_writer();

    template<typename T>
    cout_writer& operator<<(T t)
    {
        std::lock_guard<std::mutex> lock(mtx_);
        std::cout << t;
        return *this;
    }

private:
    static std::mutex mtx_;
};

} /* namespace commons */

#endif /* _COUT_WRITER_HPP */
