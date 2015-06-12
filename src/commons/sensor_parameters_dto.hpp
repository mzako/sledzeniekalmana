/**
 *  \file       sensor_parameters_dto.hpp
 *  \details    This file contains sensor_parameters_dto structure.
 *  \author     Jan Kumor
 */
#ifndef _SENSOR_PARAMETERS_HPP
#define _SENSOR_PARAMETERS_HPP

#include <cereal/cereal.hpp>

#include "vect3f.hpp"

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
    sensor_parameters_dto() {
    }
    ;
    /**
     * \brief creates sensor_parameters_dto from given values
     *
     * \param id sets #id_
     * \param mn given value of measurement noise, sets #measurement_noise_
     * \param pn given value of process noise, sets #process_noise_
     * \param r given value of radius, sets #radius_
     * \param pos given value of position, sets #position_
     */
    sensor_parameters_dto(unsigned id, float mn, float pn, float r, vect3f pos)
            : id_(id), measurement_noise_(mn), process_noise_(pn), radius_(r), position_(
                    pos) {
    }
    ;
    /**
     * \defdtr
     */
    virtual ~sensor_parameters_dto() {
    }
    ;
    /**
     * \cerealbrief
     *
     * \cerealdoc{
     * - #id_ as "id" nvp\n
     * - #measurement_noise_ as "measurement_noise" nvp\n
     * - #prosess_noise_ as "process_noise" nvp\n
     * - #radius_ as "radius" nvp\n
     * - #position_ as "position" nvp \n
     * }
     */
    template<class Archive>
    void serialize(Archive& archive) {
        archive(cereal::make_nvp("id", id_),
                cereal::make_nvp("measurement_noise", measurement_noise_),
                cereal::make_nvp("process_noise", process_noise_),
                cereal::make_nvp("radius", radius_),
                cereal::make_nvp("position", position_));
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
    /**
     * Radius of represented sensor coverage area
     */
    float radius_;
    /**
     * Position of represented sensor
     */
    vect3f position_;
};

} /* namespace commons */

#endif /* _SENSOR_PARAMETERS_HPP */
