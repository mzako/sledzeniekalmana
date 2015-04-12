#ifndef _FILTER_MODULE_HPP
#define _FILTER_MODULE_HPP

/**
 * \brief Klasa modu³u filtru.
 * \details Klasa singleton przechowuj¹ca ca³¹ logikê aplikacji filtru
 * \author Adam Moœcicki
 */

#include <vector>
#include "vect3f.hpp"
#include "kalman_filter.hpp"

class filter_module
{
public:
    static filter_module* get_instance();
    void receive_data(std::vector<vect3f> point);
    void send_data();
    void get_kalman_filter();
    void run();
private:
    kalman_filter* filter_;
    filter_module();
    filter_module(const filter_module &) = delete;
    filter_module & operator=(const filter_module &) = delete;
    static filter_module * instance_;
};


#endif //_FILTER_MODULE_HPP