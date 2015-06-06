/*
 * sensor_measurement_proxy.hpp
 *
 *  Created on: Jun 3, 2015
 *      Author: elohhim
 */

#ifndef SENSOR_MEASUREMENT_PROXY_HPP
#define SENSOR_MEASUREMENT_PROXY_HPP

#include <memory>

#include <cereal/cereal.hpp>

#include "sensor_observer.hpp"

namespace generator_app {

class sensor_measurement_proxy {
public:
    sensor_measurement_proxy( std::shared_ptr<sensor_observer> real) : real_(real) {};

    template<class Archive>
    void load(Archive& archive) {
        std::cout << "Loading sensor_measurement_proxy is illegal." << std::endl;
    }
    template<class Archive>
    void save(Archive& archive) const {
        archive(
                cereal::make_nvp("id", real_->get_id() ),
                cereal::make_nvp("measurements", real_->get_measurements() )
        );
    }

private:
    std::shared_ptr<sensor_observer> real_;
};

} /* namespace generator_app */

#endif /* SENSOR_MEASUREMENT_PROXY_HPP */
