/**
 *  \file     line.hpp
 *  \details   This file contains Line class
 *  \author    Michal Zakowski, Jan Kumor
 */

#ifndef _LINE_HPP
#define _LINE_HPP

#include "../../commons/vect3f.hpp"
#include "curve.hpp"

namespace generator_app {
namespace curves {

/**
 * \brief 3D line representation
 *
 * Represents objects' linear path in space
 */
class line : public curve {
public:
    line(commons::vect3f velocity = commons::vect3f())
            : velocity_(velocity) {
    }
    /**
     * \brief compute position
     *
     * \sa commons::vect3f curve::get_position(float time) const
     */
    commons::vect3f get_position(float time) const;
    /**
     * \brief factory method
     *
     * \param proto reference to prototype from which line will be created
     * \return smart pointer to created instance of line
     */
    static p_curve create(curve_prototype& proto) {
        float vx = proto.find_attribute("velocity.x");
        float vy = proto.find_attribute("velocity.y");
        float vz = proto.find_attribute("velocity.z");
        return p_curve(new line(commons::vect3f(vx, vy, vz)));
    }
    ;
    /**
     * \brief create prototype of line
     *
     * \sa virtual curve_prototype curve::proto() const
     */
    virtual curve_prototype proto() const {
        curve_prototype proto;
        proto.set_type("line");
        proto.insert_attribute("velocity.x", velocity_.x_);
        proto.insert_attribute("velocity.y", velocity_.y_);
        proto.insert_attribute("velocity.z", velocity_.z_);
        return proto;
    }

private:
    commons::vect3f velocity_;
};

} /* namespace curve */
} /* generator_app */
#endif
