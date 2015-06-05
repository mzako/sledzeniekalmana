/**
 *  \brief     balistic.hpp
 *  \details   This file contains balistic class
 *  \author    Michal Zakowski
 */

#ifndef _BALISTIC_HPP
#define _BALISTIC_HPP

#include <memory>

#include "../../commons/vect3f.hpp"
#include "curve.hpp"
#include "curve_prototype.hpp"

namespace generator_app {
namespace curves {

/**
 * Class line
 * Represents objects' linear path in space
 */
class balistic : public curve {
public:
    const static float GRAVITY_;

    balistic(commons::vect3f velocity = commons::vect3f(), float air_resistance=1.0) : velocity_(velocity), air_resistance_(air_resistance){};
    virtual ~balistic() {};

    commons::vect3f get_position(float) const;

    static p_curve create(curve_prototype& proto);

    virtual curve_prototype proto() const;

private:
    commons::vect3f velocity_;
    float air_resistance_;
};

} /* namespace curve */
} /* generator_app */
#endif
