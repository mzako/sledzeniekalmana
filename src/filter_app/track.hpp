#ifndef _TRACK_HPP
#define _TRACK_HPP

#include <boost/numeric/ublas/matrix.hpp>
#include "vect3f.hpp"

namespace filter_app 
{

/**
 * \biref Class implements target track with data needed to estimate its position
 * \author Adam Mościcki
 */
class track
{
public:
    track();
    ~track();
private:
    vect3f last_position;
    vect3f current_position;
    vect3f speed_vectors;
    boost::numeric::ublas::matrix<double> state_matrix;

};

}

#endif //_TRACK_HPP