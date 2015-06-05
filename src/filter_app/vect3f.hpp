/**
*  \brief     vect3f.hpp
*  \details   This file contains vect3f structure
*  \author    Michal Zakowski
*/
#ifndef _VECT3F_HPP
#define _VECT3F_HPP
namespace filter_app {
    /**
    * Struct vect3f
    * Represents objects' poistion or velocity in 3-dimensional space
    */
    struct vect3f {
        vect3f(float x = 0.f, float y = 0.f, float z = 0.f) : x_(x), y_(y), z_(z) {}
        float distance(const vect3f&) const;
        vect3f operator+(const vect3f&) const; 
        vect3f operator-(const vect3f&) const;

        float x_;
        float y_;
        float z_;
    };
}
#endif