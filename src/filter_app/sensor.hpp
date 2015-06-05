/*
 * sensor.hpp
 *
 *  Created on: Jun 4, 2015
 *      Author: elohhim
 */

#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <vector>

#include <cereal/cereal.hpp>
#include <cereal/types/vector.hpp>

#include "measurement.hpp"

namespace filter_app {

class sensor {
public:
    sensor();
    virtual ~sensor();

    template<class Archive>
    void serialize( Archive& archive) {
        archive(
                cereal::make_nvp("id", id_ ),
                cereal::make_nvp("measurements", measurements_ )
        );
    }

private:
    unsigned id_;
    std::vector<measurement> measurements_;
};

} /* namespace filter_app */

#endif /* SENSOR_HPP */
