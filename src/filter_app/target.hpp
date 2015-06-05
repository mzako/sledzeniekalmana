/**
*  \brief     target.hpp
*  \details   This file contains target class
*  \author    Michal Zakowski
*/
#ifndef _TARGET_HPP
#define _TARGET_HPP
#include <vector>
#include <memory>
#include "track.hpp"
#include <boost/numeric/ublas/matrix.hpp>
namespace filter_app {
    /**
    * Class target
    * Represents targets that change position during a simulation, moving along a given curve
    */
    class target {
    public:
        target(int sensor_id, boost::numeric::ublas::matrix<float> state, boost::numeric::ublas::matrix<float> p_factor) :
            id_(gId_++),sensor_id_(sensor_id), state_(state), p_factor_(p_factor) {}
        const boost::numeric::ublas::matrix<float>& get_state() const;
        void set_state(boost::numeric::ublas::matrix<float>);
        vect3f get_current_position() const;
        unsigned get_id() const;
        void set_sensor_id(int id){ sensor_id_ = id; }
        int get_sensor_id(){ return sensor_id_;}
        const boost::numeric::ublas::matrix<float>& get_p_factor() const;
        void set_p_factor(boost::numeric::ublas::matrix<float>);
    private:
        static unsigned gId_;
        const unsigned id_;
        unsigned sensor_id_;
        boost::numeric::ublas::matrix<float> state_;
        boost::numeric::ublas::matrix<float> p_factor_;
        track track_;
    };
}
#endif
