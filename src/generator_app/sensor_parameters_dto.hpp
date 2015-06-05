/*
 * sensor_parameters.hpp
 *
 *  Created on: Jun 5, 2015
 *      Author: elohhim
 */

#include <cereal/cereal.hpp>

#ifndef SRC_GENERATOR_APP_SENSOR_PARAMETERS_HPP_
#define SRC_GENERATOR_APP_SENSOR_PARAMETERS_HPP_

namespace generator_app {

struct sensor_parameters_dto {
    //TODO: [JKU] to jest OW
	sensor_parameters_dto() {};
    sensor_parameters_dto( unsigned id, float mn, float pn) : id_(id), measurement_noise_(mn), process_noise_(pn) {};
    virtual ~sensor_parameters_dto() {};

    template<class Archive>
    void serialize(Archive& archive)
    {
        archive(
                cereal::make_nvp("id", id_ ),
                cereal::make_nvp("measurement_noise", measurement_noise_ ),
                cereal::make_nvp("process_noise", process_noise_ )
        );
    }

    unsigned id_;
    float measurement_noise_;
    float process_noise_;

};

} /* namespace generator_app */

#endif /* SRC_GENERATOR_APP_SENSOR_PARAMETERS_HPP_ */
