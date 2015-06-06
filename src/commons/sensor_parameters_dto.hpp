/**
 *  \brief     sensor_parameters_dto.hpp
 *  \details   This file contains sensor_parameters_dto structure.
 *  \author    Jan Kumor
 */

#include <cereal/cereal.hpp>

#ifndef _SENSOR_PARAMETERS_HPP
#define _SENSOR_PARAMETERS_HPP

namespace commons {
/**
 * Struct sensor_parameters_dto
 * Data transfer object structure representing parameters of sensor.
 */
struct sensor_parameters_dto {

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

} /* namespace commons */

#endif /* _SENSOR_PARAMETERS_HPP */
