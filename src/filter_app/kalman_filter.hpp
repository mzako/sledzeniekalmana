#ifndef _KALMAN_FILTER_HPP
#define _KALMAN_FILTER_HPP

#include "target.hpp"
#include "track.hpp"

/**
 * \brief Class implements kalman filter for all targets 
 * \author Adam Mościcki
 */
class kalman_filter
{
public:
    kalman_filter();
    /**
     * \brief Returns estimated positions
     */
    std::vector<target> get_data();
    /**
     * \brief Tries to estimate real position of the targets
     */
    void estimate();
    /**
     * \brief Insert new snapshot of the observing targets
     */
    void add_new_snapshot(std::vector<target> targets);
    ~kalman_filter();
};

#endif //_KALMAN_FILTER_HPP