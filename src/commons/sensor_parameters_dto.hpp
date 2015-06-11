/**
 *  \file       sensor_parameters_dto.hpp
 *  \details    This file contains sensor_parameters_dto structure.
 *  \author     Jan Kumor
 */
#ifndef _SENSOR_PARAMETERS_HPP
#define _SENSOR_PARAMETERS_HPP

#include <cereal/cereal.hpp>

namespace commons {
/**
 * \brief Data transfer object structure representing parameters of sensor.
 *
 * Contains information about sensor's measurement parameters.
 * \dto
 */
struct sensor_parameters_dto {
    /**
     * \defcon
     */
    sensor_parameters_dto() {};
    /**
     * \brief creates sensor_parameters_dto from given id, measurement noise value and process noise value
     *
     * \param id sets #id_
     * \param mn given value of measurement noise, sets #measurement_noise_
     * \param pn given value of process noise, sets #process_noise_
     */
    sensor_parameters_dto( unsigned id, float mn, float pn) : id_(id), measurement_noise_(mn), process_noise_(pn) {};
    /**
     * \defdtr
     */
    virtual ~sensor_parameters_dto() {};
    /**
     * \cerealbrief
     *
     * \cerealdoc{
     * - #id_ as "id" nvp\n
     * - #measurement_noise_ as "measurement_noise" nvp\n
     * - #prosess_noise_ as "process_noise" nvp\n
     * }
     */
    template<class Archive>
    void serialize(Archive& archive)
    {
        archive(
                cereal::make_nvp("id", id_ ),
                cereal::make_nvp("measurement_noise", measurement_noise_ ),
                cereal::make_nvp("process_noise", process_noise_ )
        );
    }
    /**
     * Id of represented sensor
     */
    unsigned id_;
    /**
     * Measurement noise value of represented sensor
     */
    float measurement_noise_;
    /**
     * Process noise value of represented sensor
     */
    float process_noise_;
};

} /* namespace commons */

#endif /* _SENSOR_PARAMETERS_HPP */
