/**
 *  \file     environment.cpp
 *  \details   This file contains environment class' functions definitions
 *  \author    Michal Zakowski
 */

#include "environment.hpp"

#include <iterator>

#include "target.hpp"
#include "sensor_proxy_factory.hpp"

using namespace std;
using namespace commons;

namespace generator_app {

/**
 * Function set_sensors
 * Sets sensors
 */
void environment::set_sensors(std::shared_ptr<vector<std::shared_ptr<sensor_observer>>> sensors)
{
    sensors_ = sensors;
}
/**
 * Function set_sensors
 * Sets targets
 */
void environment::set_targets(std::shared_ptr<vector<std::shared_ptr<target>>> targets)
{
    targets_ = targets;
}
/**
 * Function update
 * Updates all targets in simulation
 */
void environment::update(float time)
{
    for (auto it = targets_->begin(); it != targets_->end(); ++it)
    {
        (*it)->update(time);
    }
}

std::vector<sensor_measurement_proxy> environment::get_measurements() {
    std::vector<sensor_measurement_proxy> vect;
    for (auto it = sensors_->begin(); it != sensors_->end(); it++) {
        vect.push_back( sensor_proxy_factory::get_measurement_proxy(*it) );
    }
    return vect;
}

std::vector<sensor_position_proxy> environment::get_positions() {
    std::vector<sensor_position_proxy> vect;
    for (auto it = sensors_->begin(); it != sensors_->end(); it++) {
        vect.push_back(sensor_proxy_factory::get_position_proxy((*it)));
    }
    return vect;
}

std::vector<measurement_dto> environment::get_positions2() {
    std::vector<measurement_dto> positions;
    for( auto element : *targets_ )
    {
        positions.push_back(measurement_dto(element->get_current_position(), element->get_id()));
    }
    return positions;
}


} /* namespace generator_app */
