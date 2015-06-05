/**
 *  \brief     balistic.hpp
 *  \details   This file contains balistic class
 *  \author    Michal Zakowski
 */

#ifndef _BALISTIC_HPP
#define _BALISTIC_HPP

#include <memory>

#include "curve.hpp"
#include "vect3f.hpp"

namespace generator_app {

/**
 * Class line
 * Represents objects' linear path in space
 */
class balistic : public curve {
public:
    const static float GRAVITY_;

    balistic(vect3f velocity = vect3f(), float air_resistance=1.0) : velocity_(velocity), air_resistance_(air_resistance){};
    virtual ~balistic() {};

    vect3f get_position(float) const;

    static p_curve create(curve_prototype& proto)
    {
        float air_resistance = proto.find_attribute("air_resistance");
        float vx = proto.find_attribute("velocity.x");
        float vy = proto.find_attribute("velocity.y");
        float vz = proto.find_attribute("velocity.z");
        return p_curve( new balistic( vect3f(vx, vy, vz), air_resistance));
    };

    virtual curve_prototype proto() const
    {
        curve_prototype proto;
        proto.set_type("balistic");
        proto.insert_attribute("velocity.x", velocity_.x_);
        proto.insert_attribute("velocity.y", velocity_.y_);
        proto.insert_attribute("velocity.z", velocity_.z_);
        proto.insert_attribute("air_resistance", air_resistance_);
        return proto;
    }

private:
    vect3f velocity_;
    float air_resistance_;
};

} /* generator_app */
#endif
