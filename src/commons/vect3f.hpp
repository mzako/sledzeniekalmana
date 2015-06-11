/**
 *  \brief     vect3f.hpp
 *  \details   This file contains vect3f structure
 *  \author    Michal Zakowski
 */
#ifndef VECT3F_HPP
#define VECT3F_HPP

#include <cereal/cereal.hpp>

namespace commons {
/**
 * Struct vect3f
 * Represents objects' poistion or velocity in 3-dimensional space
 */
struct vect3f {
    vect3f(float x = 0.f, float y = 0.f, float z = 0.f) : x_(x), y_(y), z_(z) {}
    float distance(const vect3f&) const;
    vect3f operator+(const vect3f&) const;
    vect3f operator-(const vect3f& vec) const;
    bool operator==(const vect3f& vec) const;

    template<class Archive>
    void serialize(Archive& archive)
    {
        archive(
                cereal::make_nvp("x", x_),
                cereal::make_nvp("y", y_),
                cereal::make_nvp("z", z_)
        );
    }

    float x_;
    float y_;
    float z_;
};

} /* namesapce commons */
#endif /* VECT3F_HPP */
