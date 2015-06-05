/**
 *  \brief     measurement.hpp
 *  \details   This file contains target class
 *  \author    Jan Kumor
 */
#ifndef _MEASUREMENT_HPP
#define _MEASUREMENT_HPP

#include <cereal/cereal.hpp>

#include "vect3f.hpp"

namespace commons {
/**
 * Class target
 * Represents targets that change position during a simulation, moving along a given curve
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
#endif
