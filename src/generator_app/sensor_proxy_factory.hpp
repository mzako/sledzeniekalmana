/**
 *  \file       sensor_proxy_factory.hpp
 *  \details    This file contains sensor_proxy_factory class
 *  \author     Jan Kumor
 */

#ifndef SENSOR_PROXY_FACTORY_HPP
#define SENSOR_PROXY_FACTORY_HPP

#include <memory>

#include "sensor_measurement_proxy.hpp"
#include "sensor_position_proxy.hpp"

namespace generator_app {
/**
 * \brief factory of \ref sensor_observer proxy objects
 */
class sensor_proxy_factory {
public:
    /**
     * \brief create sensor_measurement_proxy of given \ref sensor_observer
     *
     * \param smart pointer to \ref sensor_observer which will be proxied
     */
    static sensor_measurement_proxy get_measurement_proxy(std::shared_ptr<sensor_observer> real) {
        return sensor_measurement_proxy(real);
    }
    /**
     * \brief create sensor_position_proxy of given \ref sensor_observer
     *
     * \param smart pointer to \ref sensor_observer which will be proxied
     */
    static sensor_position_proxy get_position_proxy(std::shared_ptr<sensor_observer> real) {
        return sensor_position_proxy(real);
    }
};

} /* namespace generator_app */

#endif /* SENSOR_PROXY_FACTORY_HPP */
