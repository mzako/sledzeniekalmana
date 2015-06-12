/**
*  \file     kalman_filter.hpp
*  \details   This file contains kalman_filter class
*  \author    Michal Zakowski
*/
#ifndef _KALMAN_FILTER_HPP
#define _KALMAN_FILTER_HPP

#include <vector>
#include "target.hpp"
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include "../commons/sensor_parameters_dto.hpp"
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
        /**
        * \brief inits sensors with their parameters, targets and matrices
        *
        * \param positions represents objects' initial posiitons
        * \param sensor_parameters represents sensors' pparameters - process and measurement noise
        */
        void init_targets(std::vector<std::pair<int, commons::vect3f>> positions, std::vector<commons::sensor_parameters_dto> sensor_parameters);
        /**
        * \brief main kalman filter's computing function, uses Kalman Filter equations to compute next objects' positions
        *
        * \param new_positions new noised positions received from sensors
        */
        void compute(std::vector<commons::vect3f> new_positions);
        /**
        * \brief returns current objects' positions
        *
        * \return current computed positions
        */
        std::vector<commons::vect3f> get_current_positions() const;
        /**
        * \brief inverts square matrix
        *
        * \param input matrix to invert
        * \return inverted matrix
        */
        template<class T>
        boost::numeric::ublas::matrix<T> invert_matrix(boost::numeric::ublas::matrix<T>& input);
        /**
        * \brief determines sample rate
        */
        const static float PERIOD_;
    private:
        std::vector<std::shared_ptr<target>> targets_;
        std::map<int,std::shared_ptr<sensor_observer>> sensors_;

        boost::numeric::ublas::matrix<float> transition_;
        boost::numeric::ublas::matrix<float> output_;
    };

}
#endif //_KALMAN_FILTER_HPP

