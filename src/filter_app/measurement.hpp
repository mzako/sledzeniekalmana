/**
 *  \brief     measurement.hpp
 *  \details   This file contains target class
 *  \author    Jan Kumor
 */
#ifndef _MEASUREMENT_HPP
#define _MEASUREMENT_HPP

#include <vector>

#include <cereal/cereal.hpp>

#include "vect3f.hpp"
//TODO: [JKU] OW IDENTYCZNE JAK W generator_app, należy wydzielic powtarzające się elementy
namespace filter_app {
class measurement {
public:
    measurement() {};
    measurement(vect3f point, unsigned id) : point_(point), id_(id) {};
    unsigned get_id() const { return id_; }
    vect3f get_position() const
    {
        return point_;
    }
    template<class Archive>
    void serialize(Archive& archive) {
        archive(
                cereal::make_nvp("id", id_),
                cereal::make_nvp("measurement", point_)
        );
    }
private:
    unsigned id_;
    vect3f point_;
};

}
#endif
