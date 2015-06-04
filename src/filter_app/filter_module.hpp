#ifndef _FILTER_MODULE_HPP
#define _FILTER_MODULE_HPP

/**
 * \brief Class filter module
 * \details Singleton class containing all aplitcation filter logic
 * \author Adam Mościcki
 */

#include <vector>
#include "vect3f.hpp"
#include "kalman_filter.hpp"

namespace filter_app 
{

class filter_module
{
public:
    static filter_module* get_instance();
    /**
     * Push new position to the filter
     */
    void receive_data(std::vector<vect3f> point);
    /**
     * Move calculated position further
     */
    void send_data();
    /**
     * Starts filtring thread
     */
    void run();
private:
    std::shared_ptr<kalman_filter> filter_;
    filter_module();
    filter_module(const filter_module &) = delete;
    filter_module & operator=(const filter_module &) = delete;
    static filter_module * instance_;
};

}

#endif //_FILTER_MODULE_HPP
