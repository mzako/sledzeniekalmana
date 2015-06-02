/*
 * sensor_proxy_factory.hpp
 *
 *  Created on: Jun 3, 2015
 *      Author: elohhim
 */

#ifndef SENSOR_PROXY_FACTORY_HPP
#define SENSOR_PROXY_FACTORY_HPP

#include <memory>

#include "sensor_measurement_proxy.hpp"
#include "sensor_position_proxy.hpp"

namespace generator_app {

class sensor_proxy_factory {
public:
    static sensor_measurement_proxy get_measurement_proxy(std::shared_ptr<sensor_observer> real) {
        return sensor_measurement_proxy(real);
    }

    static sensor_position_proxy get_position_proxy(std::shared_ptr<sensor_observer> real) {
        return sensor_position_proxy(real);
    }
};

} /* namespace generator_app */

#endif /* SENSOR_PROXY_FACTORY_HPP */
