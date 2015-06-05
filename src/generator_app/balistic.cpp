/**
*  \brief     balistic.cpp
*  \details   This file contains balistic class' functions definitions
*  \author    Michal Zakowski
*/
#include <cmath>
#include "balistic.hpp"

using namespace commons;

namespace generator_app {

const float balistic::GRAVITY_ = 9.89;
/**
* Function getPosition
* Returns relative position of point moving along this line at given time
*/
vect3f balistic::get_position(float time) const
{
    vect3f pos;
    pos.x_ = log(1 + air_resistance_*velocity_.x_*time) / air_resistance_;
    if (time < velocity_.y_ / GRAVITY_){
        pos.y_ = velocity_.y_*time - GRAVITY_*time*time / 2;
    }
    else {
        pos.y_ = velocity_.y_*GRAVITY_ / 2 - GRAVITY_*time*time / 2;
    }
    pos.z_ = log(1 + air_resistance_*velocity_.z_*time) / air_resistance_;
    return pos;
}


} /* namespace generator_app */
