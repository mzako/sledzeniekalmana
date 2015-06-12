/**
 *  \file     balistic.hpp
 *  \details   This file contains balistic class
 *  \author    Michal Zakowski, Jan Kumor
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
 * \brief ballistic curve line
 *
 * Represents object's path in space in form of ballistic curve.
 * \sa curve
 */
class balistic : public curve {
public:
    /**
     * \brief Gravitational constant value used for computing
     */
    const static float GRAVITY_;
    /**
     * Creates balistic with given velocity and air_resistance factor.
     */
    balistic(commons::vect3f velocity = commons::vect3f(), float air_resistance = 1.0);
    /**
     * \defdtr
     */
    virtual ~balistic() {};
    /**
     * \brief compute position
     *
     * \sa commons::vect3f curve::get_position(float time) const
     */
    virtual commons::vect3f get_position(float time) const;
    /**
     * \brief factory method
     *
     * \param proto reference to prototype from which line will be created
     * \return smart pointer to created instance of line
     */
    static p_curve create(curve_prototype& proto);
    /**
     * \brief create prototype of ballistic curve
     *
     * \sa virtual curve_prototype curve::proto() const
     */
    virtual curve_prototype proto() const;

private:
    commons::vect3f velocity_;
    float air_resistance_;
};

} /* namespace curve */
} /* generator_app */
#endif
