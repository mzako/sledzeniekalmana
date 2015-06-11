/*
 *  \file sensor_measurement_proxy.hpp
 *  \details   This file contains sensor_measurement_proxy class
 *  \author    Jan Kumor
 */

#ifndef SENSOR_MEASUREMENT_PROXY_HPP
#define SENSOR_MEASUREMENT_PROXY_HPP

#include <memory>

#include <cereal/cereal.hpp>

#include "sensor_observer.hpp"

namespace generator_app {


/**
 * \brief Proxy allows load and save sensors measurement positions from JSON format
 *
 * Proxy which allows to easy serialize/deserialize measurements
 *
 */
class sensor_measurement_proxy {
public:
    /**
     * \brief Set sensor observer object
     *
     * Set sensor observer object from where measurement positions will be be serialized
     *
     * \param real smart pointer to sensor observer object
     */
    sensor_measurement_proxy( std::shared_ptr<sensor_observer> real) : real_(real) {};

    /**
     * \brief load method needed by Cereal to deserialize measurements
     */
    template<class Archive>
    void load(Archive& archive) {
        std::cout << "Loading sensor_measurement_proxy is illegal." << std::endl;
    }

    /**
     * \brief save method needed by Cereal to serialize measurements
     */
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
