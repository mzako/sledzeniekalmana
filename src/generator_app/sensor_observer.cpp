/**
*  \brief     sensor_observer.cpp
*  \details   This file contains SensorObserver class' functions definitions
*  \author    Michal Zakowski
*/
#include <map>
#include <list>
#include "sensor_observer.hpp"
#include "target.hpp"
#include "vect3f.hpp"
using namespace std;
/**
* Function update
* Checks whether targets entered or left sensor's area and inserts or removes target from sensor's target list
*/
void sensor_observer::update(target const* obj)
{
    list<target const*>::const_iterator it;
    for (it = targets_.begin(); it != targets_.end(); ++it){
        if (*it == obj)
            break;
    }
    if (position_.distance(obj->get_current_position()) <= radius_ && it == targets_.end()){
        targets_.push_back(obj);
    }
    else if (position_.distance(obj->get_current_position()) > radius_ && it != targets_.end()){
        targets_.erase(it);
    }
}
/**
* Function get_positions
* Returns map of pairs consisting of target's id and position
*/
map<unsigned, vect3f> sensor_observer::get_positions() const
{
    map<unsigned, vect3f> pos;
    list<target const*>::const_iterator it;
    for (it = targets_.begin(); it != targets_.end(); ++it){
        pos.insert(make_pair((*it)->get_id(), make_noise(*it)));
    }
    return pos;
}
/**
* Function make_noise
* Returns target's position with noise
*/
vect3f sensor_observer::make_noise(target const* obj) const
{
    vect3f pos;
    pos.x_ = obj->get_current_position().x_ + deviation_;
    pos.y_ = obj->get_current_position().y_ + deviation_;
    pos.z_ = obj->get_current_position().z_ + deviation_;
    return pos;
}

