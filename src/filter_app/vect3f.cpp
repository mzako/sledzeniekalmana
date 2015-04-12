#include "vect3f.hpp"


vect3f::vect3f(float x, float y, float z) : x_(x), y_(y), z_(z)
{

}

vect3f& vect3f::operator=(const vect3f & a)
{
    x_ = a.get_x();
    y_ = a.get_y();
    z_ = a.get_z();
    return *this;
}


vect3f::~vect3f()
{
}

float vect3f::get_x() const
{
    return x_;
}

float vect3f::get_y() const
{
    return y_;
}

float vect3f::get_z() const
{
    return z_;
}