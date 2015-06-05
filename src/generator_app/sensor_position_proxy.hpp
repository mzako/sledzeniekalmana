/*
 * sensor_position_proxy.hpp
 *
 *  Created on: Jun 3, 2015
 *      Author: elohhim
 */

#ifndef SENSOR_POSITION_PROXY_HPP
#define SENSOR_POSITION_PROXY_HPP

#include <memory>

#include <cereal/cereal.hpp>

#include "sensor_observer.hpp"

namespace generator_app {

class sensor_position_proxy {
public:
    sensor_position_proxy( std::shared_ptr<sensor_observer> real) : real_(real) {};

    template<class Archive>
    void serialize(Archive& archive) {
        archive (
                cereal::make_nvp("id", real_->get_id() ),
                cereal::make_nvp("targets", real_->get_positions() )
        );
    }

private:
    std::shared_ptr<sensor_observer> real_;
};

} /* namespace generator_app */

#endif /* SENSOR_POSITION_PROXY_HPP */
