/**
 *  \file     vect3f.hpp
 *  \details   This file contains vect3f structure
 *  \author    Michal Zakowski, Jan Kumor
 */
#ifndef _VECT3F_HPP
#define _VECT3F_HPP

#include <cereal/cereal.hpp>

namespace commons {
/**
 * \brief 3D vector representation
 *
 * Represents object's poistion or velocity in three-dimensional space
 */
struct vect3f {
    /**
     * \brief Creates vect3f from given coordinates
     *
     * \param x given x coordinate, sets #x_
     * \param y given y coordinate, sets #y_
     * \param z given z coordinate, sets #z_
     */
    vect3f(float x = 0.f, float y = 0.f, float z = 0.f) : x_(x), y_(y), z_(z) {}
    /**
     * \brief Euclidean distance between two points in space
     *
     * \param vec reference to vector representing second point
     * \return distance between this and vec
     */
    float distance(const vect3f&) const;
    /**
     * \brief Overloads operator+ by adding corresponding fields
     *
     * \param vec second argument of addition
     * \return result of adding this and vec
     *
     */
    vect3f operator+(const vect3f&) const;
    /**
     * \brief Overloads operator- by subtracting corresponding fields
     *
     * \param vec second argument of subtraction
     * \return result of subtracting vec from this
     */
    vect3f operator-(const vect3f& vec) const;
    /**
     * \brief Overloads operator== by comparing corresponding fields
     *
     * \param vec second argument of equals operation
     * \return true if this and vec have same coordinates otherwise false
     */
    bool operator==(const vect3f& vec) const;
    /**
     * \cerealbrief
     *
     * \cerealdoc{
     * - #x_ as "x" nvp\n
     * - #y_ as "y" nvp\n
     * - #z_ as "z" nvp\n
     * }
     */
    template<class Archive>
    void serialize(Archive& archive)
    {
        archive(
                cereal::make_nvp("x", x_),
                cereal::make_nvp("y", y_),
                cereal::make_nvp("z", z_)
        );
    }
    /**
     * x coordinate in three-dimensional CCS
     */
    float x_;
    /**
     * y coordinate in three-dimensional CCS
     */
    float y_;
    /**
     * z coordinate in three-dimensional CCS
     */
    float z_;
};

} /* namesapce commons */
#endif /* _VECT3F_HPP */
