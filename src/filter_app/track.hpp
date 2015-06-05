/**
*  \brief     track.hpp
*  \details   This file contains track class
*  \author    Michal Zakowski
*/
#ifndef _TRACK_HPP
#define _TRACK_HPP

#include <boost/numeric/ublas/matrix.hpp>

#include "target.hpp"

namespace filter_app 
{
    /**
    * Class track
    * Represents targets track during simulation
    */
    class track
    {
    public:
        void add_state(boost::numeric::ublas::matrix<float> position)
        {
            positions_.push_back(position);
        }
        const std::vector<boost::numeric::ublas::matrix<float>>& get_positions() const
        {
            return positions_;
        }
 
    private:
        std::vector<boost::numeric::ublas::matrix<float> > positions_;
    };
}
#endif //_TRACK_HPP
