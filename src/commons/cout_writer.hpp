/**
 *  \file       cout_writer.hpp
 *  \details    This file contains cout_writer class
 *  \author     Jan Kumor
 */

#ifndef _COUT_WRITER_HPP
#define _COUT_WRITER_HPP

#include <iostream>
#include <mutex>
#include <string>

namespace commons {
/**
 * \brief Allows synchronized writing to std::cout stream.
 *
 * Synchronises access to std::cout stream for multhithreading purposes.
 * Usage of static std::mutex prevents interlace of lines written from different threads.
 */
class cout_writer {
public:
    /**
     * \defcon
     */
    cout_writer();
    /**
     * \defdtr
     */
    virtual ~cout_writer();

    /**
     * \brief Overloaded operator<< template, allows convenient stream-like usage.
     *
     * Typical usage:
     * \code
     * cout_writer() << something << '\n';
     * \endcode
     * \b Note: std::endl is not supported, although in most cases what you really mean is end of line ( in explicit '\\n') not manual buffer flush, so i don't consider it as flaw.
     *
     * \param t object which will be passed to std::cout stream
     * \return reference to this
     */
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
