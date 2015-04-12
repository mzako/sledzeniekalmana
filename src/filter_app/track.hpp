#ifndef _TRACK_HPP
#define _TRACK_HPP


/**
 * \biref Class implements target track with data needed to estimate its position
 * \author Adam Mościcki
 */

#include <boost/numeric/ublas/matrix.hpp>
#include "vect3f.hpp"


class track
{
public:
    track();
    ~track();
private:
    vect3f lastPosition;
    vect3f currentPosition;
    
};

#endif //_TRACK_HPP