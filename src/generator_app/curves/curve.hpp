/**
 *  \file     curve.hpp
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
 * \brief abstract representation of curve
 *
 * Represents curve, which determines objects' path in space.
 * Allows computation of position in given time.
 */
class curve {
public:
    /**
     * \defdtr
     */
    virtual ~curve();
    /**
     * \brief computation of position in given time
     *
     * \param time given time
     * \return relative position of point moving along this curve at given time
     */
    virtual commons::vect3f get_position(float time) const = 0;
    /**
     * \brief create prototype of curve
     *
     * \return prototype of this
     */
    virtual curve_prototype proto() const = 0;
};

typedef std::shared_ptr<curve> p_curve;

} /* namespace curve */
} /* namespace generator_app */
#endif
