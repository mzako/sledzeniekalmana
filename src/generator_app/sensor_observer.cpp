/**
 *  \brief     sensor_observer.cpp
 *  \details   This file contains SensorObserver class' functions definitions
 *  \author    Michal Zakowski
 */
#include <map>
#include <list>
#include <random>
#include "sensor_observer.hpp"
#include "target.hpp"
#include "vect3f.hpp"
using namespace std;
using namespace generator_app;

unsigned sensor_observer::gId_ = 1;
/**
 * Function update
 * Checks whether targets entered or left sensor's area and inserts or removes target from sensor's target list
 */
void sensor_observer::update(std::shared_ptr<target> obj)
{
    list<std::shared_ptr<target>>::iterator it;
    for (it = targets_.begin(); it != targets_.end(); ++it){
        if (*it == obj)
            break;
    }
    //TODO iterator end!
    if (position_.distance(obj->get_current_position()) <= radius_ /*&& it == targets_.end()*/){
        targets_.push_back(obj);
    }
    else if (position_.distance(obj->get_current_position()) > radius_ /*&& it != targets_.end()*/){
        targets_.erase(it);
    }
    measurements_.clear();
    for (it = targets_.begin(); it != targets_.end(); ++it){
        measurements_.push_back( make_measurement(*it) );
    }
}
/**
 * Function measure targets position
 * Returns measurement which is target's position with noise
 */
measurement sensor_observer::make_measurement(std::shared_ptr<target> obj) const
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> d(mean_, deviation_);
    vect3f pos;
    pos.x_ = obj->get_current_position().x_ + d(gen);
    pos.y_ = obj->get_current_position().y_ + d(gen);
    pos.z_ = obj->get_current_position().z_ + d(gen);
    return measurement( pos, obj->get_id() );
}

