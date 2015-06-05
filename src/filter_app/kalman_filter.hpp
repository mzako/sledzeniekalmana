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
#include "../generator_app/sensor_parameters_dto.hpp"
#include "sensor_observer.hpp"

namespace filter_app 
{
    /**
    * Class kalman_filter
    * Represents kalman filter and its logic
    */

    class kalman_filter
    {
    public:
        void init_targets(std::vector<std::pair<int, vect3f>>, std::vector<generator_app::sensor_parameters_dto>);
        void compute(std::vector<vect3f>);
        std::vector<vect3f> get_current_positions() const;
        void print(boost::numeric::ublas::matrix<float>&);
        template<class T>
        boost::numeric::ublas::matrix<T> invert_matrix(boost::numeric::ublas::matrix<T>&);

        const static float PERIOD_;
    private:
        std::vector<std::shared_ptr<target>> targets_;
        std::map<int,std::shared_ptr<sensor_observer>> sensors_;

        boost::numeric::ublas::matrix<float> transition_;
        boost::numeric::ublas::matrix<float> output_;
    };

}
#endif //_KALMAN_FILTER_HPP

