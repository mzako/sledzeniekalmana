/*
 *  \file sensor_position_proxy.hpp
 *  \details   This file contains sensor_position_proxy class
 *  \author    Jan Kumor
 */

#ifndef SENSOR_POSITION_PROXY_HPP
#define SENSOR_POSITION_PROXY_HPP

#include <memory>
#include <cereal/cereal.hpp>
#include "sensor_observer.hpp"

namespace generator_app {

/**
 * \brief Proxy allows load and save real sensors positions from JSON format
 *
 * Proxy which allows to easy serialize/deserialize positions
 *
 */
class sensor_position_proxy {
public:
    /**
     * \brief Set sensor observer object
     *
     * Set sensor observer object from where real positions will be be serialized
     *
     * \param real smart pointer to sensor observer object
     */
    sensor_position_proxy(std::shared_ptr<sensor_observer> real)
            : real_(real) {
    }
    ;

    /**
     * \brief load method needed by Cereal to deserialize real positons
     */
    template<class Archive>
    void load(Archive& archive) {
        std::cout << "Loading sensor_position_proxy is illegal." << std::endl;
    }

    /**
     * \brief load method needed by Cereal to serialize real positons
     */
    template<class Archive>
    void save(Archive& archive) const {
        archive(cereal::make_nvp("id", real_->get_id()),
                cereal::make_nvp("positions", real_->get_positions()));
    }

private:
    std::shared_ptr<sensor_observer> real_;
};

} /* namespace generator_app */

#endif /* SENSOR_POSITION_PROXY_HPP */
