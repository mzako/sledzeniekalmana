/**
 *  \brief     balistic.cpp
 *  \details   This file contains balistic class' functions definitions
 *  \author    Michal Zakowski
 */
#include "balistic.hpp"

#include <cmath>

using namespace commons;

namespace generator_app {
namespace curves {

const float balistic::GRAVITY_ = 9.89;
/**
* Constructor
*/
balistic::balistic(commons::vect3f velocity, float air_resistance) : velocity_(velocity)
{
    if (air_resistance < 0)
    {
        air_resistance_ = 0;
    }
    else
    {
        air_resistance_ = air_resistance;
    }
}
/**
 * Function getPosition
 * Returns relative position of point moving along this line at given time
 */
vect3f balistic::get_position(float time) const
{
    vect3f pos;
    if (air_resistance_ == 0)
    {
        pos.x_ = velocity_.x_*time;
        pos.y_ = velocity_.y_*time;
        pos.z_ = velocity_.z_*time - GRAVITY_*time*time / 2;
    }
    else
    {
        pos.x_ = log(1 + air_resistance_*velocity_.x_*time) / air_resistance_;
        pos.y_ = log(1 + air_resistance_*velocity_.y_*time) / air_resistance_;
        pos.z_ = velocity_.z_*time - GRAVITY_*time*time / 2;
    }
    return pos;
}

p_curve balistic::create(curve_prototype& proto)
{
    float air_resistance = proto.find_attribute("air_resistance");
    float vx = proto.find_attribute("velocity.x");
    float vy = proto.find_attribute("velocity.y");
    float vz = proto.find_attribute("velocity.z");
    return p_curve( new balistic( commons::vect3f(vx, vy, vz), air_resistance));
};

curve_prototype balistic::proto() const
{
    curve_prototype proto;
    proto.set_type("balistic");
    proto.insert_attribute("velocity.x", velocity_.x_);
    proto.insert_attribute("velocity.y", velocity_.y_);
    proto.insert_attribute("velocity.z", velocity_.z_);
    proto.insert_attribute("air_resistance", air_resistance_);
    return proto;
}

} /* namespace curve */
} /* namespace generator_app */
