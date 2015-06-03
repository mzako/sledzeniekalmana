/**
 *  \brief     target.hpp
 *  \details   This file contains target class
 *  \author    Michal Zakowski
 */
#ifndef _TARGET_HPP
#define _TARGET_HPP
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
class target {
public:
    target() {};
    target(std::shared_ptr<curve> curve, vect3f initial_position = vect3f()) :curve_(curve), initial_position_(initial_position), current_position_(initial_position), id_(gId_++) {}
    void update(float);
    void set_sensor_observers(std::shared_ptr<std::vector<std::shared_ptr<sensor_observer>>>);
    vect3f get_current_position() const;
    vect3f get_initial_position() const;
    unsigned get_id() const;
    std::shared_ptr<curve> get_curve() const { return curve_; }

    template<class Archive>
    void serialize(Archive& archive)
    {
        archive(
                cereal::make_nvp("id", id_),
                cereal::make_nvp("position", current_position_)
        );
    }
private:
    void notify();

    static unsigned gId_;
    unsigned id_;
    vect3f initial_position_;
    vect3f current_position_;
    std::shared_ptr<curve> curve_;
    std::shared_ptr<std::vector<std::shared_ptr<sensor_observer>>> observers_;
};

typedef std::shared_ptr<target> p_target;
}
#endif
