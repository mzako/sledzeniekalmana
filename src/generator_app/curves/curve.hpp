/**
 *  \brief     curve.hpp
 *  \details   This file contains curve class
 *  \author    Michal Zakowski
 */

#ifndef _CURVE_HPP
#define _CURVE_HPP

#include <memory>

#include "../../commons/vect3f.hpp"
#include "curve_prototype.hpp"

namespace generator_app {
namespace curves {

/**
 * Class curve (abstract)
 * Represents curve, which determines objects' path in space
 */
class curve {
public:
    virtual commons::vect3f get_position(float) const = 0;
    virtual curve_prototype proto() const = 0;
};

typedef std::shared_ptr<curve> p_curve;

} /* namespace curve */
} /* namespace generator_app */
#endif
