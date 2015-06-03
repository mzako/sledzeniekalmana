/**
*  \brief     measurement.hpp
*  \details   This file contains target class
*  \author    Jan Kumor
*/
#ifndef _MEASUREMENT_HPP
#define _MEASUREMENT_HPP
#include <vector>
#include <memory>

#include <cereal/cereal.hpp>

#include "curve.hpp"
#include "sensor_observer.hpp"
namespace generator_app {
    class sensor_observer;
    /**
    * Class target
    * Represents targets that change position during a simulation, moving along a given curve
    */
    class measurement {
    public:
        measurement() {};
        measurement(vect3f point, unsigned id) : point_(point), id_(id) {};
        unsigned get_id() const { return id_; }

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