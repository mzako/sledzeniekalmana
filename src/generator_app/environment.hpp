/**
*  \brief     environment.hpp
*  \details   This file contains environment class
*  \author    Michal Zakowski
*/

#ifndef _ENVIRONMENT_HPP
#define _ENVIRONMENT_HPP
#include <vector>
#include <map>
#include "target.hpp"
/**
* Class environment
* Represents simulation world, contains objects and sensors
*/
class environment {
public:
    void update(unsigned);
    std::map<unsigned, vect3f> getPositions() const;
    void set_sensors(std::vector<sensor_observer*>);
    void set_targets(std::vector<target*>);
private:
    std::vector<sensor_observer *> sensors_;
    std::vector<target *> targets_;
};
#endif