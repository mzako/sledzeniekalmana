/**
*  \brief     target.hpp
*  \details   This file contains target class
*  \author    Michal Zakowski
*/
#ifndef _TARGET_HPP
#define _TARGET_HPP
#include <vector>
#include "curve.hpp"
#include "sensor_observer.hpp"

class sensor_observer;
/**
* Class target
* Represents targets that change position during a simulation, moving along a given curve
*/
class target {
public:
    target(curve* curve, vect3f initial_position = vect3f()) :curve_(curve), initial_position_(initial_position), current_position_(initial_position), id_(gId_++) {}
    void update(unsigned);
    void set_sensor_observers(std::vector<sensor_observer* > *);
    vect3f get_current_position() const;
    vect3f get_initial_position() const;
    unsigned get_id() const;
private:
    void notify();

    static unsigned gId_;
    const unsigned id_;
    vect3f initial_position_;
    vect3f current_position_;
    curve* curve_;
    std::vector<sensor_observer* > * observers_;
};
#endif