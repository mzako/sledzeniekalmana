/**
 *  \file     sensor_observer.cpp
 *  \details   This file contains SensorObserver class' functions definitions
 *  \author    Michal Zakowski
 */
#include <map>
#include <list>
#include <random>
#include "sensor_observer.hpp"
#include "simulation_module.hpp"
#include "target.hpp"

using namespace std;
using namespace commons;

namespace generator_app {

unsigned sensor_observer::gId_ = 1;

void sensor_observer::update(p_target obj)
{
    list<p_target>::iterator it;
    for (it = targets_.begin(); it != targets_.end(); ++it)
    {
        if (*it == obj)
        {
            break;
        }
    }
    if( it == targets_.end() )
    {
        if (position_.distance(obj->get_current_position()) <= radius_)
        {
            targets_.push_back(obj);
        }
    }
    else if (position_.distance(obj->get_current_position()) > radius_)
    {
        cout << "c";
        targets_.erase(it);
    }
    cout << "d";
    measurements_.clear();
    for (it = targets_.begin(); it != targets_.end(); ++it){
        measurements_.push_back(make_measurement(*it));
    }
}

measurement_dto sensor_observer::make_measurement(std::shared_ptr<target> obj) const
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> d(0, simulation_module::TIME_STEP_*simulation_module::TIME_STEP_/2);
    vect3f pos;
    pos.x_ = obj->get_current_position().x_ + d(gen)*measurement_noise_;
    pos.y_ = obj->get_current_position().y_ + d(gen)*measurement_noise_;
    pos.z_ = obj->get_current_position().z_ + d(gen)*measurement_noise_;
    return measurement_dto( pos, obj->get_id() );
}

std::vector<measurement_dto> sensor_observer::get_positions() const {
    std::vector<measurement_dto> positions;
    for( auto element : targets_ )
    {
        positions.push_back(measurement_dto(element->get_current_position(), element->get_id()));
    }
    return positions;
}

std::vector<measurement_dto> sensor_observer::get_measurements() const
{
    return measurements_;
}

} /* namespace generator_app */
