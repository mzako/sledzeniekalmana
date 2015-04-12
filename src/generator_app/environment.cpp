/**
*  \brief     environment.cpp
*  \details   This file contains environment class' functions definitions
*  \author    Michal Zakowski
*/
#include <vector>
#include "environment.hpp"
using namespace std;
/**
* Function set_sensors
* Sets sensors
*/
void environment::set_sensors(std::vector<sensor_observer*> sensors)
{
    sensors_ = sensors;
}
/**
* Function set_sensors
* Sets targets
*/
void environment::set_targets(std::vector<target*> targets)
{
    targets_ = targets;
}
/**
* Function getPositions
* Returns collection of pairs consisting of objects' id and current position
*/
std::map<unsigned, vect3f> environment::getPositions() const
{
    std::map<unsigned, vect3f> pos;
    vector<target*>::const_iterator it;
    for (it = targets_.begin(); it != targets_.end(); ++it){
        pos.insert(make_pair((*it)->get_id(), (*it)->get_current_position()));
    }
    return pos;
}
/**
* Function update
* Updates all targets in simulation
*/
void environment::update(unsigned time)
{
    vector<target*>::iterator it;
    for (it = targets_.begin(); it != targets_.end(); ++it){
        (*it)->update(time);
    }
}