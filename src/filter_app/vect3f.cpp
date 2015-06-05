/**
*  \brief     vect3f.cpp
*  \details   This file contains vect3f class' functions definitions
*  \author    Michal Zakowski
*/
#include <cmath>

#include "vect3f.hpp"

namespace filter_app {

/**
* Function distance
* Returns Euclidean distance between two points in space
*/
float vect3f::distance(const vect3f& vec) const
{
    float dx, dy, dz;
    dx = x_ - vec.x_;
    dy = y_ - vec.y_;
    dz = z_ - vec.z_;
    return sqrt(dx*dx + dy*dy + dz*dz);
}
/**
* Function operator+
* Overloads operator+ by adding corresponding fields
*/
vect3f vect3f::operator+(const vect3f& vec) const
{
    return vect3f(x_ + vec.x_, y_ + vec.y_, z_ + vec.z_);
}
/**
* Function operator-
* Overloads operator- by subtracting corresponding fields
*/
vect3f vect3f::operator-(const vect3f& vec) const
{
    return vect3f(x_ - vec.x_, y_ - vec.y_, z_ - vec.z_);
}

}
