/**
*  \brief     kalman_filter.hpp
*  \details   This file contains kalman_filter class
*  \author    Michal Zakowski
*/
#ifndef _KALMAN_FILTER_HPP
#define _KALMAN_FILTER_HPP

#include <vector>
#include "target.hpp"
#include "track.hpp"
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/lu.hpp>

namespace filter_app 
{
    /**
    * Class kalman_filter
    * Represents kalman filter and its logic
    */

    class kalman_filter
    {
    public:
        void init_targets(std::vector<vect3f>, std::vector<std::pair<float, float> >);
        void compute(std::vector<vect3f>);
        std::vector<vect3f> get_current_positions() const;
        void print(boost::numeric::ublas::matrix<float>&);
        template<class T>
        boost::numeric::ublas::matrix<T> invert_matrix(boost::numeric::ublas::matrix<T>&);

        const static float PERIOD_;
    private:
        std::vector<std::shared_ptr<target>> targets_;
        std::vector<boost::numeric::ublas::matrix<float> > p_factors_;
        std::vector<boost::numeric::ublas::matrix<float> > process_covariances_;
        std::vector<boost::numeric::ublas::matrix<float> > meas_covariances_;
        boost::numeric::ublas::matrix<float> transition_;
        boost::numeric::ublas::matrix<float> output_;
    };

}
#endif //_KALMAN_FILTER_HPP

