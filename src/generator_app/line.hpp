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
    private:
        vect3f velocity_;
    };
}
#endif