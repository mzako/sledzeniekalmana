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
        target(boost::numeric::ublas::matrix<float> state = boost::numeric::ublas::matrix<float> (6,1,0)) :
            id_(gId_++), state_(state) {}
        const boost::numeric::ublas::matrix<float>& get_state() const;
        void set_state(boost::numeric::ublas::matrix<float>);
        vect3f get_current_position() const;
        unsigned get_id() const;
    private:
        static unsigned gId_;
        const unsigned id_;
        boost::numeric::ublas::matrix<float> state_;
        track track_;
    };
}
#endif