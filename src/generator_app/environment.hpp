/**
 *  \file environment.hpp
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
 * \brief Simulation environment
 *
 * Represents simulation world containing objects and sensors
 */
class environment {
public:
    /**
     * \brief updates all targets in simulation
     *
     * For each target call its update method
     */
    void update(float);

    /**
     * \setter{sensors_}
     *
     */
    void set_sensors(std::shared_ptr<std::vector<std::shared_ptr<sensor_observer>>>);

    /**
     * \setter{targets_}
     */
    void set_targets(std::shared_ptr<std::vector<std::shared_ptr<target>>>);

    /**
     * \getter{sensors_}
     */

    std::shared_ptr<std::vector<p_sensor_observer>> get_sensors() const { return sensors_; }

    /**
     * \brief Returns proxies for measurements
     *
     * Makes proxies for measurements from sensor - needed to easy serialize by Cereal
     */
    std::vector<sensor_measurement_proxy> get_measurements();

    /**
      * \getter{positions_}
      *
      * Makes proxies for positions from sensor - needed to easy serialize by  Cereal
      *
      * \sa{sensor_position_proxy}
      */
    std::vector<sensor_position_proxy> get_positions();

    /**
     * \getter{positions2_}
     *
     * For each positon makes corresponding measurement data transfer objects
     *
     * \sa{sensor_measurement_proxy}
     */
    std::vector<commons::measurement_dto> get_positions2();

private:
    std::shared_ptr<std::vector<p_sensor_observer>> sensors_;
    std::shared_ptr<std::vector<p_target>> targets_;
};

} /* namespace generator_app */
#endif
