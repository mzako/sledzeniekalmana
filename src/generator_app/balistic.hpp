/**
*  \brief     balistic.hpp
*  \details   This file contains balistic class
*  \author    Michal Zakowski
*/

#ifndef _BALISTIC_HPP
#define _BALISTIC_HPP
#include "vect3f.hpp"
#include "curve.hpp"
namespace generator_app {
    /**
    * Class line
    * Represents objects' linear path in space
    */
    class balistic : public curve {
    public:
        balistic(vect3f velocity = vect3f(), float air_resistance=1.0) : velocity_(velocity), air_resistance_(air_resistance){}
        vect3f get_position(float) const;

        const static float GRAVITY_;
    private:
        vect3f velocity_;
        float air_resistance_;
    };
}
#endif