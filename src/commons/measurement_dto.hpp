/**
 *  \brief     measurement_dto.hpp
 *  \details   This file contains measurement_dto structure.
 *  \author    Jan Kumor
 */
#ifndef _MEASUREMENT_DTO_HPP
#define _MEASUREMENT_DTO_HPP

#include <cereal/cereal.hpp>

#include "vect3f.hpp"

namespace commons {

/**
 * Struct measurement_dto
 * Data transfer object structure representing sampled target position.
 */
struct measurement_dto {
    measurement_dto() {};
    measurement_dto(vect3f point, unsigned id) : point_(point), id_(id) {};
    unsigned get_id() const { return id_; }

    template<class Archive>
    void serialize(Archive& archive) {
        archive(
                cereal::make_nvp("id", id_),
                cereal::make_nvp("measurement", point_)
        );
    }
    unsigned id_;
    vect3f point_;
};
}
#endif /* _MEASUREMENT_DTO_HPP */
