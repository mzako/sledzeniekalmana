/**
 *  \brief     environment.hpp
 *  \details   This file contains environment class
 *  \author    Michal Zakowski
 */

#ifndef _ENVIRONMENT_HPP
#define _ENVIRONMENT_HPP
#include <vector>
#include <map>
#include <iostream>

#include "target.hpp"
#include "measurement.hpp"

namespace generator_app {
/**
 * Class environment
 * Represents simulation world, contains objects and sensors
 */
class environment {
public:
    void update(float);
    void set_sensors(std::shared_ptr<std::vector<std::shared_ptr<sensor_observer>>>);
    void set_targets(std::shared_ptr<std::vector<std::shared_ptr<target>>>);

    std::shared_ptr<std::vector<std::shared_ptr<sensor_observer>>> getSensors() const {
        return sensors_;
    }

    std::vector<sensor_measurement_proxy> get_measurements() {
        std::vector<sensor_measurement_proxy> vect;
        for(auto it = sensors_->begin(); it != sensors_->end(); it++) {
            vect.push_back( sensor_proxy_factory::get_measurement_proxy((*it)) );
        }
        return vect;
    };

    std::vector<sensor_position_proxy> get_positions() {
        std::vector<sensor_position_proxy> vect;
        for(auto it = sensors_->begin(); it != sensors_->end(); it++) {
            vect.push_back( sensor_proxy_factory::get_position_proxy((*it)) );
        }
        return vect;
    };

private:
    std::shared_ptr<std::vector<std::shared_ptr<sensor_observer>>> sensors_;
    std::shared_ptr<std::vector<std::shared_ptr<target>>> targets_;
};
}
#endif
