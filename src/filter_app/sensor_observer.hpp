/**
 *  \brief     sensor_observer.hpp
 *  \details   This file contains sensor_observer class
 *  \author    Michal Zakowski
 */

#ifndef SENSOROBSERVER_HPP
#define SENSOROBSERVER_HPP
#include <map>
#include <list>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/lu.hpp>

#include "target.hpp"

namespace filter_app {
    /**
     * Class sensor_observer
     * Represents sensor gathering data about objects' position during simulation
     */
    class sensor_observer {
    public:
        sensor_observer(int id, boost::numeric::ublas::matrix<float> measurement_covariance, 
            boost::numeric::ublas::matrix<float> process_covariance):measurement_covariance_(measurement_covariance),
            process_covariance_(process_covariance), id_(id) {}
        unsigned get_id() const { return id_; }
        /*void set_measurement_covariance(boost::numeric::ublas::matrix<float> measurement_covariance)
        {
            measurement_covariance_ = measurement_covariance;
        }
        void set_process_covariance(boost::numeric::ublas::matrix<float> process_covariance)
        {
            process_covariance_ = process_covariance;
        }*/
        boost::numeric::ublas::matrix<float> get_measurement_covariance() const
        {
            return measurement_covariance_;
        }
        boost::numeric::ublas::matrix<float> get_process_covariance() const
        {
            return process_covariance_;
        }
        /*std::list<std::shared_ptr<target>> get_targets() { return targets_; }
        void add_target(std::shared_ptr<target> target){
            targets_.push_back(target);
        }*/
    private:
        unsigned id_;
        boost::numeric::ublas::matrix<float> process_covariance_;
        boost::numeric::ublas::matrix<float> measurement_covariance_;
    };
}
#endif
