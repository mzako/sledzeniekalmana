#ifndef _KALMAN_FILTER_HPP
#define _KALMAN_FILTER_HPP

#include <vector>
#include "target.hpp"
#include "track.hpp"
#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/matrix.hpp>

namespace filter_app 
{

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
private:
    boost::shared_ptr<std::vector<boost::shared_ptr<target>>> targets; //make sure that it is correct
    //for all targets following matrixes are the same (I think how far i understand it).
    boost::numeric::ublas::matrix<double> transition_matrix; 
    boost::numeric::ublas::matrix<double> observation_model_matrix; 
    boost::numeric::ublas::matrix<double> process_noise_matrix; 
    boost::numeric::ublas::matrix<double> observation_noise_matrix; 
    
};

}

#endif //_KALMAN_FILTER_HPP