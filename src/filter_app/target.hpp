/**
*  \brief     target.hpp
*  \details   This file contains target class
*  \author    Michal Zakowski
*/
#ifndef _TARGET_HPP
#define _TARGET_HPP
#include <vector>
#include <memory>

#include <boost/numeric/ublas/matrix.hpp>

#include "../commons/vect3f.hpp"


namespace filter_app {
    /**
    * Class target
    * Represents targets that change position during a simulation, moving along a given curve
    */
    class target {
    public:
        target(int sensor_id, boost::numeric::ublas::matrix<float> state, boost::numeric::ublas::matrix<float> p_factor) :
            id_(gId_++),sensor_id_(sensor_id), state_(state), p_factor_(p_factor) {}
        /**
        * \brief return current state vector as matrix, which consists of position and velocity
        *
        * \return targets current state vector
        */
        const boost::numeric::ublas::matrix<float>& get_state() const;
        /**
        * \brief set new target's state computed by kalman filter
        *
        * \param new target's state
        */
        void set_state(boost::numeric::ublas::matrix<float> state);
        /**
        * \brief return current target's position
        *
        * \return current target's position
        */
        commons::vect3f get_current_position() const;
        /**
        * \brief return unique target id, which is maintained in filter's logic
        *
        * \return target id
        */
        unsigned get_id() const;
        /**
        * \brief set unique sensor id, which reaches target
        *
        * \param id sensor id
        */
        void set_sensor_id(int id){ sensor_id_ = id; }
        /**
        * \brief return unique sensor id, which reaches target
        *
        * \return sensor id
        */
        int get_sensor_id(){ return sensor_id_;}
        /**
        * \brief return target's p_factor, which changes in every iteration and is used in kalman filter equations
        *
        * \return target's p_factor
        */
        const boost::numeric::ublas::matrix<float>& get_p_factor() const;
        /**
        * \brief set target's p_factor, which changes in every iteration and is used in kalman filter equations
        *
        * \param pfactor target's updated p_factor
        */
        void set_p_factor(boost::numeric::ublas::matrix<float> pfactor);
    private:
        static unsigned gId_;
        const unsigned id_;
        unsigned sensor_id_;
        boost::numeric::ublas::matrix<float> state_;
        boost::numeric::ublas::matrix<float> p_factor_;
    };
}
#endif
