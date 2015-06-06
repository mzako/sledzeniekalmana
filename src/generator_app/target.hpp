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

#include "curves/curve.hpp"
#include "curves/curve_factory.hpp"
#include "curves/curve_prototype.hpp"

#include "sensor_observer.hpp"

namespace generator_app {

class sensor_observer;
typedef std::shared_ptr<sensor_observer> p_sensor_observer;

/**
 * Class target
 * Represents targets that change position during a simulation, moving along a given curve
 */
class target : public std::enable_shared_from_this<target> {
public:
    target() {};
    target(curves::p_curve curve, commons::vect3f initial_position = commons::vect3f()) :curve_(curve), initial_position_(initial_position), current_position_(initial_position), id_(gId_++) {}
    virtual ~target();
    void update(float);
    void set_sensor_observers(std::shared_ptr<std::vector<p_sensor_observer> >);
    commons::vect3f get_current_position() const;
    commons::vect3f get_initial_position() const;
    unsigned get_id() const;
    curves::p_curve get_curve() const { return curve_; }

    template <class Archive>
    void save( Archive& archiver )
    {
        archiver(
                cereal::make_nvp("initial_position", initial_position_),
                cereal::make_nvp("curve", curve_->proto() )
        );
    };
    template <class Archive>
    void load( Archive& archiver )
    {
        curves::curve_prototype cp;
        archiver(
                cereal::make_nvp("initial_position", initial_position_),
                cereal::make_nvp("curve", cp )
        );
        curve_ = curves::curve_factory::get_instance().create(cp);
    };

private:
    void notify();

    static unsigned gId_;
    unsigned id_;
    commons::vect3f initial_position_;
    commons::vect3f current_position_;
    curves::p_curve curve_;
    std::shared_ptr<std::vector<p_sensor_observer> > observers_;
};

typedef std::shared_ptr<target> p_target;

class target_load_proxy {
public:
    target_load_proxy() {}
    target_load_proxy(p_target real) : real_(real) {}
    p_target get_real() const { return real_; }

    template<class Archive>
    void save(Archive& archive) const
    {
        archive(
                cereal::make_nvp("target", *real_)
        );
    }

    template<class Archive>
    void load(Archive& archive)
    {
        real_.reset();
        real_ = p_target( new target() );
        archive(
                cereal::make_nvp("target", *real_)
        );
    }

private:
    p_target real_;
};
}
#endif
