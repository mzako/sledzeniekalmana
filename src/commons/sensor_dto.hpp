/**
 *  \file       sensor_dto.hpp
 *  \details    This file contains sensor_dto structure
 *  \author     Jan Kumor
 */
#ifndef _SENSOR_DTO_HPP
#define _SENSOR_DTO_HPP

#include <vector>

#include <cereal/cereal.hpp>
#include <cereal/types/vector.hpp>

#include "measurement_dto.hpp"

namespace commons {
/**
 * \brief Data transfer object representing sensor and positions of all targets seen by it.
 *
 * Contains information about sensors's id and targets positions.
 * \dto
 */
struct sensor_dto {
    /**
     * \defcon
     */
    sensor_dto() {};
    /**
     * \defdtr
     */
    virtual ~sensor_dto() {};
    /**
     * \refgetter{#measurements_}
     */
    std::vector<measurement_dto>& get_measurements() {
        return measurements_;
    }
    /**
     * \getter{#id_}
     */
    int get_id() const { return id_; }
    /**
     * \cerealbrief
     *
     * \cerealdoc{
     * - #id_ as "id" nvp\n
     * - #measurements_\n
     * }
     */
    template<class Archive>
    void serialize( Archive& archive) {
        archive(
                cereal::make_nvp("id", id_ ),
                //TODO: [JKU] maybe this should always be nvp target and add field telling about type
                measurements_
        );
    }
    /**
     * Id of represented sensor
     */
    unsigned id_;
    /**
     * Vector of targets seen by sensor representations.
     * \sa measurement_dto
     */
    std::vector<measurement_dto> measurements_;
};

} /* namespace commons */

#endif /* _SENSOR_DTO_HPP */
