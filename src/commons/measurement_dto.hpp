/**
 *  \file       measurement_dto.hpp
 *  \details    This file contains measurement_dto structure
 *  \author     Jan Kumor
 */
#ifndef _MEASUREMENT_DTO_HPP
#define _MEASUREMENT_DTO_HPP

#include <cereal/cereal.hpp>

#include "vect3f.hpp"

namespace commons {
/**
 * \brief Data transfer object representing target's position.
 *
 * Contains information about target's id and position.
 * \dto
 */
//TODO: [JKU] Maybe change to target_dto?
struct measurement_dto {
    /**
     * \defcon
     */
    measurement_dto() {
    }
    ;
    /**
     * \brief Constructor creating measurement_dto from given point and id.
     *
     *  \param point given point
     *  \param id given id
     */
    measurement_dto(vect3f point, unsigned id)
            : point_(point), id_(id) {
    }
    ;
    /**
     * \cerealbrief
     *
     * \cerealdoc{
     * - #id_ as "id" nvp\n
     * - #point_ as "coordinates" nvp\n
     * }
     */
    template<class Archive>
    void serialize(Archive& archive) {
        archive(cereal::make_nvp("id", id_),
                cereal::make_nvp("coordinates", point_));
    }
    /**
     * Id of represented target
     */
    unsigned id_;
    /**
     * Position of represented target
     */
    vect3f point_;
};
}
#endif /* _MEASUREMENT_DTO_HPP */
