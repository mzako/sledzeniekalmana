/**
 *  \brief     line.hpp
 *  \details   This file contains Line class
 *  \author    Michal Zakowski
 */

#ifndef _LINE_HPP
#define _LINE_HPP

#include "vect3f.hpp"
#include "curve.hpp"

namespace generator_app {

/**
 * Class line
 * Represents objects' linear path in space
 */
class line : public curve {
public:
    line(vect3f velocity = vect3f()) : velocity_(velocity) {}
    vect3f get_position(float) const;

    static p_curve create( curve_prototype& proto )
    {
        float vx = proto.find_attribute("velocity.x");
        float vy = proto.find_attribute("velocity.y");
        float vz = proto.find_attribute("velocity.z");
        return p_curve( new line( vect3f(vx, vy, vz) ) );
    };

    virtual curve_prototype proto() const
    {
        curve_prototype proto;
        proto.set_type("line");
        proto.insert_attribute("velocity.x", velocity_.x_);
        proto.insert_attribute("velocity.y", velocity_.y_);
        proto.insert_attribute("velocity.z", velocity_.z_);
        return proto;
    }

private:
    vect3f velocity_;
};

} /* generator_app */
#endif
