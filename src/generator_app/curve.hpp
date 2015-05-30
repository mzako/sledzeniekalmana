/**
*  \brief     curve.hpp
*  \details   This file contains curve class 
*  \author    Michal Zakowski
*/

#ifndef _CURVE_HPP
#define _CURVE_HPP
#include "vect3f.hpp"
namespace generator_app {
    /**
    * Class curve (abstract)
    * Represents curve, which determines objects' path in space
    */
    class curve {
    public:
        virtual vect3f get_position(float) const = 0;
    };
}
#endif