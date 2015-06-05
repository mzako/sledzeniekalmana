/**
*  \brief     line.cpp
*  \details   This file contains Line class' functions definitions
*  \author    Michal Zakowski
*/
#include "line.hpp"

using namespace commons;
namespace generator_app {

/**
* Function getPosition
* Returns relative position of point moving along this line at given time
*/
vect3f line::get_position(float time) const
{
    return vect3f(velocity_.x_*time, velocity_.y_*time, velocity_.z_*time);
}

} /* namespace generator_app */
