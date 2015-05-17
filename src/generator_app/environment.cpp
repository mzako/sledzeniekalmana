/**
*  \brief     environment.cpp
*  \details   This file contains environment class' functions definitions
*  \author    Michal Zakowski
*/
#include <vector>
#include "environment.hpp"
using namespace std;
using namespace generator_app;
/**
* Function set_sensors
* Sets sensors
*/
void environment::set_sensors(boost::shared_ptr<vector<boost::shared_ptr<sensor_observer>>> sensors)
{
    sensors_ = sensors;
}
/**
* Function set_sensors
* Sets targets
*/
void environment::set_targets(boost::shared_ptr<vector<boost::shared_ptr<target>>> targets)
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
    vector<boost::shared_ptr<sensor_observer>>::const_iterator it;
    for (it = sensors_->begin(); it != sensors_->end(); ++it){
        std::map<unsigned, vect3f> sensor_pos = (*it)->get_positions();
        if (sensor_pos.size())
            pos.insert(sensor_pos.begin(), sensor_pos.end());
    }
    return pos;
}
/**
* Function update
* Updates all targets in simulation
*/
void environment::update(unsigned time)
{
    vector<boost::shared_ptr<target>>::iterator it;
    for (it = targets_->begin(); it != targets_->end(); ++it){
        (*it)->update(time);
    }
}