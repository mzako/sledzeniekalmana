/**
 *  \brief     curve.hpp
 *  \details   This file contains curve class
 *  \author    Michal Zakowski
 */

#ifndef _CURVE_HPP
#define _CURVE_HPP

#include <memory>

#include "curve_prototype.hpp"
#include "vect3f.hpp"

namespace generator_app {

/**
 * Class curve (abstract)
 * Represents curve, which determines objects' path in space
 */
class curve {
public:
    virtual vect3f get_position(float) const = 0;
    virtual curve_prototype proto() const = 0;
};

typedef std::shared_ptr<curve> p_curve;

} /* namespace generator_app */
#endif
