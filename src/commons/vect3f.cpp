/**
 *  \file    vect3f.cpp
 *  \details This file contains vect3f class' functions definitions
 *  \author  Michal Zakowski
 */
#include <cmath>

#include "vect3f.hpp"

namespace commons {
float vect3f::distance(const vect3f& vec) const
{
    float dx, dy, dz;
    dx = x_ - vec.x_;
    dy = y_ - vec.y_;
    dz = z_ - vec.z_;
    return sqrt(dx*dx + dy*dy + dz*dz);
}

vect3f vect3f::operator+(const vect3f& vec) const
{
    return vect3f(x_ + vec.x_, y_ + vec.y_, z_ + vec.z_);
}

vect3f vect3f::operator-(const vect3f& vec) const
{
    return vect3f(x_ - vec.x_, y_ - vec.y_, z_ - vec.z_);
}

bool vect3f::operator==(const vect3f& vec) const
{
    if (this == &vec)
    {
        return true;
    }
    if (x_ == vec.x_ && y_ == vec.y_ && z_ == vec.z_)
    {
        return true;
    }
    return false;
}

} /* namespace commons */
