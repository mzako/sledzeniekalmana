/**
 *  \brief     environment.hpp
 *  \details   This file contains environment class
 *  \author    Michal Zakowski
 */

#ifndef _ENVIRONMENT_HPP
#define _ENVIRONMENT_HPP

#include <memory>
#include <vector>

#include "sensor_measurement_proxy.hpp"
#include "sensor_position_proxy.hpp"
#include "target.hpp"

#include "../commons/measurement_dto.hpp"

namespace generator_app {
class sensor_observer;
class target;
} /* namespace generator_app */

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

    std::shared_ptr<std::vector<p_sensor_observer>> get_sensors() const { return sensors_; }

    std::vector<sensor_measurement_proxy> get_measurements();

    std::vector<sensor_position_proxy> get_positions();
    std::vector<commons::measurement_dto> get_positions2();

private:
    std::shared_ptr<std::vector<p_sensor_observer>> sensors_;
    std::shared_ptr<std::vector<p_target>> targets_;
};

} /* namespace generator_app */
#endif
